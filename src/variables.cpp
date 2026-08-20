#include <utility>
#include <tannic/variables.hpp>

namespace tannic::expressions { 
     
auto Variable::index() const noexcept -> Index const& {
    return index_;
}

auto Variable::vertex() const noexcept -> Vertex const& {
    return vertex_;
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