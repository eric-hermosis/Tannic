#include <utility> 
#include <tannic/graph.hpp>
#include <tannic/variables.hpp>

namespace tannic {
    
Variable::Variable(Scope scope) {
    node_ = Node::allocate(scope);
    node_->acquire();
}

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

void Variable::release() { 
    if (node_) {
        node_-> release();  
        node_ = nullptr;
    }  
}

auto Variable::forward() const -> Node* {
    if (!node_) {    
        node_ = Node::allocate(Scope::Local);
        node_->acquire();
    }
}

}