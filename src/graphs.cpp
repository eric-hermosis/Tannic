#include <cassert>
#include <utility> 
#include <tannic/symbols.hpp>
#include <tannic/types.hpp>
#include <tannic/layouts.hpp>
#include <tannic/graphs.hpp>

#include <iostream>

namespace tannic { 
  
struct node_t {
    const char* name;
};

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
    
void Node::set(Symbol const& symbol) {
    tag_ = symbol.name();   
}

void Node::reset() {  
    tag_ = std::string_view{};
}

}