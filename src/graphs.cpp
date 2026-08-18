#include <cassert>
#include <utility> 
#include <stack>
#include <vector>
#include <tannic/c/graphs.h>
#include <tannic/symbols.hpp>
#include <tannic/types.hpp>
#include <tannic/layouts.hpp>
#include <tannic/graphs.hpp>

#include <iostream>

namespace tannic { 
    
Node::Node(Index index)
:   index_(index)
,   links_(0) {
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

auto Node::index() const -> Index {
    return index_;
}  

static thread_local struct { 
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

    new (body_) node_t {
        .name = "Unknown",
        .type = unknown,
        .layout {
            .rank = 0,
            .size = 1
        }
    };
}

void Node::set(Symbol const& symbol) noexcept {
    body_->name = symbol.name().data();
}

void Node::set(Type const& type) noexcept {
    body_->type = type;
}

void Node::set(Layout const& layout) noexcept { 

    body_->layout = layout_t {
        .rank = layout.rank(),
        .size = layout.size()
    };
 
    for (auto index = 0; index < layout.rank(); index++) {
        body_->layout.shape.sizes[index] = layout.size(index);
        body_->layout.strides.sizes[index] = layout.stride(index);
    }
}

void Node::release() noexcept {    
    local.free.push(body_);
    body_ = nullptr;
}

}