#include <mutex>
#include <stack>
#include <vector>
#include <cassert>
#include <utility>
#include <tannic/context.hpp>
#include <tannic/graph.hpp>

namespace tannic {
    
Node::Node()
:   links_(0) {
    priors_.reserve(4);     
}

static struct {
    std::mutex mutex; 
    std::stack<Node> stack;
} global;

static thread_local struct {  
    std::stack<Node> stack;
    std::stack<Node*, std::vector<Node*>> free;
} local;
 
void Node::acquire() noexcept {
    assert(state_);
    if (state_->scope() == Scope::Local) {
        ++links_;
    }
}

void Node::release() noexcept { 
    assert(state_);
    if (state_->scope() == Scope::Local) {
        assert(links_ > 0);
        if (--links_ == 0) {
            reset();
            local.free.push(this);
        }
    }
}

void Node::link(Node* source) noexcept {
    assert(source);
    source->acquire();
    priors_.push_back(source);
}

void Node::prune() noexcept {
    for (auto node : priors_) {
        node->release();
    }
    priors_.clear();
}

void Node::set(State* state) noexcept {
    assert(!state_);
    state_ = state;
    state_-> acquire();
}

void Node::reset() noexcept {
    assert(state_);
    state_-> release();
    state_ = nullptr;
    prune();
}

void Graph::preallocate(std::size_t count) {
    while (local.stack.size() < count) {
        local.free.emplace(&local.stack.emplace());
    }
}

auto Graph::allocate(Context const& context) -> Node* {

    auto scope = context.scope();
    
    switch (scope) {
        
        case Scope::Local: {

            if (local.free.empty()) {
                auto node = &local.stack.emplace();   
                node->set(context.allocate());
                return node;
            } 

            else {
                auto node = local.free.top();
                node->set(context.allocate());
                local.free.pop();
                return node;
            }
        }

        case Scope::Global: {
            std::lock_guard lock(global.mutex);
            auto node = &global.stack.emplace();
            node->set(context.allocate());
            return node;
        }

        default:
            std::unreachable();
    }
}

auto Graph::capacity() -> std::size_t {
    return local.stack.size();
}

auto Graph::available() -> std::size_t {
    return local.free.size();
}

}