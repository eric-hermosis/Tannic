#include <cassert>
#include <utility> 
#include <stack>
#include <vector>
#include <tannic/c/graphs.h>
#include <tannic/symbols.hpp>
#include <tannic/types.hpp>
#include <tannic/layouts.hpp>
#include <tannic/graphs.hpp>
#include <tannic/environments.hpp>

#include <iostream>

namespace tannic { 
    
Node::Node()
:   links_(0) {
    sources_.reserve(4);
}

void Node::bump() {
    ++links_;
}

bool Node::dump() {
    assert(links_ > 0);
    return --links_ == 0;
}

void Node::link(Node* source) {
    sources_.push_back(source);
}

void Node::prune() {
    sources_.clear();
} 

static struct { 
    std::stack<node_t> arena;
    std::stack<node_t*, std::vector<node_t*>> free;
} local; 

void Node::acquire() noexcept {
    if (local.free.empty()) {
        body_ = &local.arena.emplace();
    } 
    
    else {
        body_ = local.free.top();
        local.free.pop();
    } 
}

void Node::set(Symbol const& symbol, Type const& type, Layout const& layout) noexcept { 
    assert(body_);
    shape_t shape;
    strides_t strides;

    for (auto dimension = 0; dimension < layout.rank(); dimension++) {
        shape.sizes[dimension] = layout.size(dimension);
        strides.sizes[dimension] = layout.stride(dimension);
    }

    new (body_) node_t {
        .kind = EXPRESSION,
        .expression { 
            .name = symbol.name().data(),
            .type = type,
            .layout {
                .rank = layout.rank(),
                .size = layout.size(),
                .shape = shape,
                .strides = strides
            }
        } 
    };
}

void Node::set(Handler const& handler) noexcept { 
    assert(body_);

    new (body_) node_t {
        .kind = COMPUTATION
    };
}

void Node::set(Environment const& environment) noexcept { 
    assert(body_);

    new (body_) node_t {
        .kind = ALLOCATION
    };
}

void Node::reset() noexcept {
    new (body_) node_t;
} 
  
void Node::release() noexcept {     
    local.free.push(body_);
    body_ = nullptr;  
} 

}