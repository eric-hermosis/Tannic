#include <cassert>
#include <utility> 
#include <tannic/graph.hpp>
#include <tannic/variables.hpp>

namespace tannic {
    
void Variable::copy(Variable const& other) {
    if (node_ != other.node_) {  
        if (other.node_) {
            other.node_ -> acquire();
        }
        release();
        node_ = other.node_;
    }
}

void Variable::move(Variable & other) noexcept {
    if (node_ != other.node_) {
        release();
        node_ = std::exchange(other.node_, nullptr);
    }
}

void Variable::acquire(Node* node) {
    if (node_) {
        node_-> release();  
    }
    node_ = node;
    node_->acquire();
}

void Variable::release() { 
    if (node_) {
        node_-> release();  
        node_ = nullptr;
    }  
}

void Variable::initialize(Scope scope) const {
    assert(!node_);
    node_ = Node::allocate(scope);
    node_->acquire();
}

auto Variable::forward() const -> Node* {
    if (!node_) {    
        initialize(Scope::Global); 
    }
    return node_;
}

}