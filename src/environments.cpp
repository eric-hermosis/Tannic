#include <tannic/environments.hpp>

namespace tannic {

Environment::Environment(Host const& host) 
:   domain_(host) {}

Environment::Environment(Device const& device) 
:   domain_(device) {}

Environment::operator bool() const noexcept {
    return !std::holds_alternative<std::monostate>(domain_); 
}

}