#include <utility>
#include <cassert>
#include <tannic/trace.hpp>
#include <tannic/graph.hpp>

namespace tannic::expression {


Vertex::Vertex(Type const& type) {
    node_ = Node::allocate();
    node_-> set(type);
    node_-> acquire();
} 

void Vertex::release() { 
    if (node_) {
        node_-> release();  
        node_ = nullptr;
    }  
}

void Vertex::copy(Vertex const& other) {
    if (node_ != other.node_) {  
        if (other.node_) {
            other.node_-> acquire();
        }
        release();
        node_ = other.node_;
    }
}

void Vertex::move(Vertex & other) noexcept { 
    if (node_ != other.node_) {
        release();
        node_ = std::exchange(other.node_, nullptr);
    }
}

void Vertex::link(Vertex const& other) { 
    assert(node_);
    node_->link(other.node_);
}
 
void Vertex::prune() {
    assert(node_);
    node_->prune();
}
 
}