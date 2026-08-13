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

void Variable::acquire(Node* node) const noexcept {
    if (node_) {
        node_-> release();  
    }
    node_ = node;
    node_->acquire();
}

void Variable::release() const noexcept { 
    if (node_) {
        node_-> release();  
        node_ = nullptr;
    }  
}

}