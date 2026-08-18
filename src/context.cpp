#include <tannic/context.hpp>

namespace tannic {

void Context::set(Environment const& environment) noexcept {
    environment_ = environment;
}

}