#include <stack>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <tannic/visitors.hpp>

namespace tannic {

void Visitor::visit(std::size_t index) noexcept {
    visits_[index] = generation_;
}

bool Visitor::visited(std::size_t  index) const noexcept {
    return visits_[index] == generation_;
}

void Visitor::set(std::size_t size) {
    const std::size_t size_ = size + 1;

    if (visits_.size() < size_) {
        visits_.resize(size_, 0);
    }
}

void Visitor::reset() noexcept {
    if (++generation_ == 0) {
        std::fill(visits_.begin(), visits_.end(), 0);
        generation_ = 1;
    }
} 

}