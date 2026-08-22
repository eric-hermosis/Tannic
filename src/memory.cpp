#include <cassert>
#include <utility> 
#include <stack>
#include <vector>
#include <tannic/c/allocations.h>
#include <tannic/memory.hpp>
#include <tannic/environments.hpp>

namespace tannic {

Memory::Memory()
:   references_(0) {}

void Memory::bump() noexcept {
    ++references_;
}

bool Memory::dump() noexcept {
    assert(references_ > 0);
    return --references_ == 0;
}

static struct { 
    std::stack<allocation_t> arena;
    std::stack<allocation_t*, std::vector<allocation_t*>> free;
} allocations; 

void Memory::acquire() noexcept {
    if (allocations.free.empty()) {
        body_ = &allocations.arena.emplace();
    } 
    
    else {
        body_ = allocations.free.top();
        allocations.free.pop();
    } 
}

void Memory::release() noexcept {     
    allocations.free.push(body_);
    body_ = nullptr;  
} 

void Memory::set(std::size_t size, Environment const& environment) noexcept { 
    assert(body_); 
    auto const& allocator = environment.allocator(); 
    
    new (body_) allocation_t { 
        .domain = HOST,
        .allocator = {
            .name       = allocator.name.data(),
            .allocate   = allocator.allocate,
            .deallocate = allocator.deallocate
        },
        .buffer = {
            .size    = size,
            .address = nullptr
        }
    }; 

} 

void Memory::reset() noexcept {
    assert(body_ && !body_->buffer.address);
    new (body_) allocation_t {};
} 

void Memory::allocate() {
    assert(body_ && !body_->buffer.address);
    body_->buffer.address = body_->allocator.allocate(body_->buffer.size);   
}

void Memory::deallocate() noexcept {
    assert(body_ && body_->buffer.address);   
    body_->allocator.deallocate(body_->buffer.address, body_->buffer.size);   
    body_->buffer.address = nullptr;
}

auto Memory::body() const noexcept -> Body* {
    return body_;
}

}