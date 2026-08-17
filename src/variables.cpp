#include <utility>
#include <tannic/variables.hpp>

namespace tannic::expressions { 
    
void Variable::acquire() const noexcept {
    if(!vertex_) {
        vertex_ = Vertex(symbol());
    }
    vertex_.acquire();
}

void Variable::release() const noexcept {
    if (vertex_) {
        vertex_.release();
    }
    vertex_ = Vertex();
}

void Variable::copy(Variable const& other) const {
    if (vertex_ != other.vertex_) {   
        if (vertex_) {
            vertex_.release();        
        } 

        if (other.vertex_) {
            other.vertex_.acquire();
            vertex_ = other.vertex_;
        } 
    }
}

void Variable::move(Variable & other) const noexcept {
    if (vertex_ != other.vertex_) {
        if (vertex_) {
            vertex_.release();        
        } 
        vertex_ = std::exchange(other.vertex_, Vertex());
    }
}


}