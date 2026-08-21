#include <stack>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <tannic/schedules.hpp>

namespace tannic {

static struct {
    std::stack<std::unique_ptr<Visitor>> stack;
} visitor;

Scheduler::Scheduler(std::size_t size) {
    if (visitor.stack.empty()) {
        visitor_ = std::make_unique<Visitor>();
    } 
    
    else {
        visitor_ = std::move(visitor.stack.top());
        visitor.stack.pop();
    }

    visitor_->set(size);
}

Scheduler::~Scheduler() {
    visitor_->reset();
    visitor.stack.push(std::move(visitor_));
}

}