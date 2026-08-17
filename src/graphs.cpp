#include <cassert>
#include <utility> 
#include <tannic/symbols.hpp>
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
    std::cout << symbol.name() << std::endl;
    body_ = new node_t {
        .name = symbol.name().data()
    };
}

void Node::reset() {
    std::cout << "Deletion!" << std::endl;
    assert(body_);
    delete body_;
    body_ = nullptr;
}

}