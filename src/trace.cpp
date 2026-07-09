#include <stack>
#include <vector> 
#include <cassert>
#include <tannic/trace.hpp>

namespace tannic::expression {

Node::Node() {}

Node::~Node() {}

static thread_local struct {
    std::stack<Node> stack;
    std::stack<Node*, std::vector<Node*>> free;
} nodes;

auto Node::allocate() -> Node* {
    if (nodes.free.empty()) {
        nodes.free.push(&nodes.stack.emplace());
    }
    auto node = nodes.free.top();
    nodes.free.pop(); 
    return node;
}

void Node::set(Type const& type) noexcept {
    
}

void Node::link(Node* source) noexcept  {
    assert(source);
    source->acquire();
    sources_.push_back(source);
}

void Node::acquire() noexcept {
    ++links_;
}

void Node::release() noexcept  {
    if (--links_ == 0) {
        prune();
        nodes.free.push(this);
    }
}

void Node::prune() noexcept  {
    for (auto node : sources_) {
        node->release();
    } 
    sources_.clear();
}

} namespace tannic::execution {

Node::Node() {}

Node::~Node() {}

static thread_local struct {
    std::stack<Node> stack;
    std::stack<Node*, std::vector<Node*>> free;
} nodes;

auto Node::allocate() -> Node* {
    if (nodes.free.empty()) {
        nodes.free.push(&nodes.stack.emplace());
    }
    auto node = nodes.free.top();
    nodes.free.pop(); 
    return node;
}

void Node::link(Node* source) noexcept  {
    assert(source);
    source->acquire();
    sources_.push_back(source);
}

void Node::acquire() noexcept  {
    ++links_;
}

void Node::release() noexcept {
    if (--links_ == 0) {
        prune();
        nodes.free.push(this);
    }
}

void Node::prune() noexcept {
    for (auto node : sources_) {
        node->release();
    } 
    sources_.clear();
}

Nodes::Nodes(std::size_t count) {
    list_.resize(count);
}

void Nodes::resize(std::size_t count) noexcept {
    list_.resize(count);
} 

void Nodes::set(std::size_t index, Node* node) noexcept {
    assert(list_[index] == nullptr);
    list_[index] = node;
    node->acquire();
}

auto Nodes::get(std::size_t index) noexcept  -> Node* {
    return list_[index];
}

bool Nodes::has(std::size_t index) noexcept  {
    return list_[index] ? true : false;
}

void Nodes::clear() noexcept  {
    for(auto index = 0; index < list_.size(); ++index) {
        auto node = list_[index];
        if (node) {
            node->release(); 
            list_[index] = nullptr;
        } 
    }
}

}