#include <iostream>
#include <tannic/layouts.hpp>

#include <iostream>
#include <tannic/c/types.h>
#include <tannic/c/layouts.h> 
#include <tannic/types.hpp>
#include <tannic/layouts.hpp>

namespace tannic::io {
 
void print(std::ostream& stream, rank_type rank) {
    stream << static_cast<int>(rank);
}

void print(std::ostream& stream, type type) {
    stream << traits[type].name;
}

void print(std::ostream& stream, const shape_t& shape, rank_type dimensions, bool reference = true) {
    stream << "(";
    for (rank_type dimension = 0; dimension < dimensions; ++dimension) { 
        stream << (reference ? shape.address[dimension] : shape.sizes[dimension]);

        if (dimension + 1 < dimensions) {
            stream << ", ";
        }
    }
    stream << ")"; 
}

void print(std::ostream& stream, const strides_t& strides, rank_type dimensions, bool reference = true) {
    stream << "(";
    for (rank_type dimension = 0; dimension < dimensions; ++dimension) { 
        stream << (reference ? strides.address[dimension] : strides.sizes[dimension]);
        if (dimension + 1 < dimensions) {
            stream << ", ";
        }
    }
    stream << ")"; 
}   

} namespace tannic {

auto operator<<(std::ostream& stream, Type const& type) -> std::ostream&{
    io::print(stream, type);
    return stream;
}

auto operator<<(std::ostream& stream, Shape const& shape) -> std::ostream&{
    shape_t printable { .address = shape.address() };
    stream << "Shape"; 
    io::print(stream, printable, shape.size());
    return stream;
} 

auto operator<<(std::ostream& stream, Strides const& strides) -> std::ostream& {
    strides_t printable { .address = strides.address() };
    stream << "Strides"; 
    io::print(stream, printable, strides.size());
    return stream;
} 

}