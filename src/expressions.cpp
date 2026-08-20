#include <stack>
#include <vector>
#include <cassert>
#include <tannic/graphs.hpp> 
#include <tannic/expressions.hpp> 

namespace tannic::expressions {
 
Index::Index(std::size_t value)
:   value_(value) {}

Index::operator bool() const noexcept {
    return value_ != 0;
}

Index::operator std::size_t() const noexcept {
    return value_;
}

auto Index::value() const noexcept -> std::size_t {
    return value_;
}

auto Index::forward() noexcept -> Index {
    return Index(++value_);
}

static thread_local struct {
    std::size_t index = 0;
    std::stack<Node> arena;
    std::stack<Node*, std::vector<Node*>> free;
} local;

Vertex::operator bool() const noexcept {
    return node_ != nullptr;
}

bool Vertex::operator==(Vertex const& other) const noexcept {
    return node_ == other.node_;
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

void Vertex::acquire() noexcept {
    if (!node_) { 
        if (local.free.empty()) {
            node_ = &local.arena.emplace();
        }

        else {
            node_ = local.free.top();
            local.free.pop();
        }
        node_->acquire();
    }
    node_->bump();
}

void Vertex::release() noexcept {
    if (node_ && node_->dump()) {
        node_->prune();
        node_->reset();
        node_->release();
        local.free.push(node_);
        node_ = nullptr;
    } 
} 

void Vertex::set(Symbol const& symbol, Type const& type, Layout const& layout) noexcept {   
    node_->set(symbol, type, layout);
} 

}