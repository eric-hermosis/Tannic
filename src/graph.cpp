#include <mutex>
#include <stack>
#include <vector>
#include <cassert>
#include <utility>
#include <tannic/graph.hpp>

namespace tannic {
    
Node::Node(Index index, Scope scope)
:   index_(index)
,   scope_(scope)
,   links_(0) {
    priors_.reserve(4);     
}

static struct {
    std::mutex mutex;
    std::size_t index = 0;
    std::stack<Node> stack;
} global;

static thread_local struct {
    std::size_t index = 0;
    std::stack<Node> stack;
    std::stack<Node*, std::vector<Node*>> free;
} local;

auto Node::index() const noexcept -> Index {
    return index_;
}

auto Node::scope() const noexcept -> Scope {
    return scope_;
}

void Node::acquire() noexcept {
    if (scope_ == Scope::Local) {
        ++links_;
    }
}

void Node::release() noexcept {
    assert(links_ > 0);
    if (scope_ == Scope::Local) {
        if (--links_ == 0) {
            prune();
            local.free.push(this);
        }
    }
}

void Node::link(Node* source) noexcept {
    source->acquire();
    priors_.push_back(source);
}

void Node::prune() noexcept {
    for (auto node : priors_) {
        node->release();
    }
    priors_.clear();
}

void Graph::preallocate(std::size_t count) {
    while (local.stack.size() < count) {
        local.free.emplace(&local.stack.emplace(local.index++, Scope::Local));
    }
}

auto Graph::allocate(Scope scope) -> Node* {
 
    switch (scope) {
        
        case Scope::Local: {

            if (local.free.empty()) {
                return &local.stack.emplace(local.index++, scope);
            } 

            else {
                auto node = local.free.top();
                local.free.pop();
                return node;
            }
        }

        case Scope::Global: {
            std::lock_guard lock(global.mutex);
            return &global.stack.emplace(global.index++, scope);
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