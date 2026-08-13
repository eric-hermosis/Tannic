#include <mutex>
#include <deque>
#include <stack>
#include <vector>
#include <stdexcept>
#include <utility>
#include <tannic/context.hpp>

namespace tannic {

static struct {
    std::size_t index;
    std::mutex mutex;
    std::deque<State> arena;
} global;

static thread_local struct {
    std::size_t index;
    std::stack<State> arena;
    std::stack<State*, std::vector<State*>> free;
} local;

State::State(Index index, Scope scope)
:   index_(index)
,   scope_(scope) {}

auto State::index() const noexcept -> Index {
    return index_;
}

auto State::scope() const noexcept -> Scope {
    return scope_;
}

void State::acquire() noexcept {
    //
}

void State::release() noexcept {
    if (scope_ == Scope::Local) {
        local.free.push(this);
    }
}

Context::Context(Scope scope)
:   scope_(scope) {}

auto Context::scope() const noexcept -> Scope {
    return scope_;
}

auto Context::allocate() const noexcept -> State* {

    switch (scope_) {

        case Scope::Local: { 

            if (local.free.empty()) {
                return &local.arena.emplace(local.index++, scope_);
            } 

            else {
                auto node = local.free.top();
                local.free.pop();
                return node;
            } 
        }

        case Scope::Global: { 
            std::lock_guard lock(global.mutex);
            return &global.arena.emplace_back(global.index++, scope_);
        }
        
        default:
            std::unreachable();
        }
} 
 
}