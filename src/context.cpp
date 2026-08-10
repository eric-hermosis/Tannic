#include <tannic/context.hpp>

namespace tannic {

Context::Context(Scope scope)
:   scope_(scope) {}

auto Context::scope() const noexcept -> Scope {
    return scope_;
}

}