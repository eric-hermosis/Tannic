#include <stack>
#include <vector>
#include <cassert>
#include <tannic/graphs.hpp>
#include <tannic/symbols.hpp>
#include <tannic/expressions.hpp> 

namespace tannic::expressions {
 
static thread_local struct {
    std::size_t index = 0;
    std::stack<Node> arena;
    std::stack<Node*, std::vector<Node*>> free;
} local;

Vertex::Vertex(Symbol const& symbol) {
    if (local.free.empty()) {
        node_ = &local.arena.emplace(local.index++);
    }

    else {
        node_ = local.free.top();
        local.free.pop();
    }
    node_->set(symbol);
}

Vertex::operator bool() noexcept {
    return node_ != nullptr;
}

bool Vertex::operator==(Vertex const& other) const noexcept {
    return node_ == other.node_;
}

void Vertex::acquire() noexcept {
    assert(node_);
    node_->bump();
}

void Vertex::release() noexcept {
    assert(node_);
    if (node_->dump()) {
        node_->prune();
        node_->reset();
        local.free.push(node_);
        node_ = nullptr;
    } 
}

void Vertex::succeed(Vertex const& other) {
    assert(node_);
    assert(other.node_);
    node_->link(other.node_);
}

void Vertex::precede(Vertex const& other) {
    assert(node_);
    assert(other.node_);
    other.node_->link(node_);
}

}