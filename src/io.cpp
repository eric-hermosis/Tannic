#include <ostream>
#include <tannic/types.hpp>

namespace tannic::io {

void print(std::ostream& stream, type type) {
    stream << types::traits[type].name;
}

} namespace tannic {

auto operator<<(std::ostream& stream, Type const& type) -> std::ostream& {
    io::print(stream, type);
    return stream;
}

}