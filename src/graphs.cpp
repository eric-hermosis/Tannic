#include <cassert>
#include <utility> 
#include <stack>
#include <vector>
#include <tannic/c/graphs.h>
#include <tannic/symbols.hpp>
#include <tannic/types.hpp>
#include <tannic/layouts.hpp>
#include <tannic/graphs.hpp>

namespace tannic {
    
Node::Node()
:   references_(0) {
    sources_.reserve(4);
}

void Node::bump() noexcept {
    ++references_;
}

bool Node::dump() noexcept {
    assert(references_ > 0);
    return --references_ == 0;
}

void Node::link(Node* source) {
    sources_.push_back(source);
}

void Node::prune() {
    sources_.clear();
} 

static struct { 
    std::stack<expression_t> arena;
    std::stack<expression_t*, std::vector<expression_t*>> free;
} pool; 

void Node::acquire() noexcept {
    if (pool.free.empty()) {
        body_ = &pool.arena.emplace();
    } 
    
    else {
        body_ = pool.free.top();
        pool.free.pop();
    } 
}

void Node::release() noexcept {     
    pool.free.push(body_);
    body_ = nullptr;  
} 

void Node::set(Symbol const& symbol, Type const& type, Layout const& layout) noexcept { 
    assert(body_);
    shape_t shape;
    strides_t strides;

    for (auto dimension = 0; dimension < layout.rank(); dimension++) {
        shape.sizes[dimension] = layout.size(dimension);
        strides.sizes[dimension] = layout.stride(dimension);
    }

    new (body_) expression_t {  
        .name = symbol.name().data(),
        .type = type,
        .layout {
            .rank = layout.rank(),
            .size = layout.size(),
            .shape = shape,
            .strides = strides
        } 
    };
} 

void Node::reset() noexcept {
    assert(body_);
    new (body_) expression_t {};
} 

auto Node::body() const noexcept -> Body* {
    return body_;
}

}