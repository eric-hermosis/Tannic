#include <cstdlib>
#include <tannic/environments.hpp>
#include <tannic/exceptions.hpp>

namespace tannic {

Host::Host() {
    allocator_ = Allocator(
        "malloc",
        [](std::size_t size) noexcept -> void* { return std::malloc(size); },
        [](void* address, std::size_t size) noexcept -> void { std::free(address); }
    );
}

auto Host::allocator() const -> Allocator const& {
    return allocator_;
}

Environment::Environment(Host const& host) 
:   domain_(host) {}
  
Environment::operator bool() const noexcept {
    return !std::holds_alternative<std::monostate>(domain_); 
}
 
[[nodiscard]] auto Environment::allocator() const -> Allocator const& {
    if (std::holds_alternative<Host>(domain_)) {    
        return std::get<Host>(domain_).allocator();
    }

    else {
        throw Error("Requesting allocator from invalid domain.");
    }
}

}