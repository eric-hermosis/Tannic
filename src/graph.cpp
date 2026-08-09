#include <stack>
#include <vector>
#include <tannic/graph.hpp>

namespace tannic {
    
Node::Node(Index index, Scope scope)
:   index_(index)
,   scope_(scope)
,   links_(0) {
    priors_.reserve(4);     
}

static struct {
    std::size_t index = 0;
    std::stack<Node> stack;
} global;

static thread_local struct {
    std::size_t index = 0;
    std::stack<Node> stack;
    std::stack<Node*, std::vector<Node*>> free;
} local;

auto Node::allocate(Scope scope) -> Node* {
    switch (scope) {
        
        case Scope::Local: 

            if (local.free.empty()) {
                return &local.stack.emplace(local.index++, scope);
            } 

            else {
                auto node = local.free.top();
                local.free.pop();
                return node;
            }
    
        case Scope::Global:
            return &global.stack.emplace(local.index++, scope);
        
        default:
            [[unreachable]]; 
    }
}

auto Node::index() const noexcept -> Index {
    return index_;
}

void Node::acquire() noexcept {
    switch (scope_) {
        case Scope::Local:
            ++links_;
            break;
        
        case Scope::Global:
            break;

        default:
            [[unreachable]]; 
    }
}

void Node::release() noexcept {
    switch (scope_) {
        case Scope::Local:
            if (--links_ == 0) {
                prune();
                local.free.push(this);
            }
            break;
        
        case Scope::Global:
            break;

        default:
            [[unreachable]]; 
    }
}

void Node::link(Node* source) {
    source->acquire();
    priors_.push_back(source);
}

void Node::prune() {
    for (auto node : priors_) {
        node->release();
    }

    priors_.clear();
}

}