#include <stack>
#include <tannic/trace.hpp>
#include <tannic/execution.hpp>

namespace tannic::execution {

Handle::Handle() {
    node_ = nullptr;
}

Handle::Handle(Node* node) {
    node_ = node;
}

static thread_local struct {
    std::stack<std::unique_ptr<Nodes>> free;
} cache;

Handles::Handles(std::size_t count) {
    if (cache.free.empty()) {
        nodes_ = std::make_unique<Nodes>(count);
    } 
    
    else {
        nodes_ = std::move(cache.free.top());
        cache.free.pop();
    }
} 

auto Handles::create(Index index) -> Handle {
    auto node = Node::allocate();
    nodes_->set(index, node);
    return node;
}

void Handles::set(Index index, Handle const& handle) {
    nodes_->set(index, handle.node_);
}

bool Handles::has(Index index) {
    return nodes_->has(index);
}

auto Handles::get(Index index) -> Handle {
    return Handle(nodes_->get(index));
}

}