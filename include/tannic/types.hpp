// Copyright 2026 Eric Hermosis
//
// This file is part of the Tannic Tensor Library.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
#ifndef TYPES_HPP_0x45524943
#define TYPES_HPP_0x45524943 

#include <iosfwd>
#include <cstdint>
#include <cstddef>
#include <string_view> 
#include <complex>  
#include <tuple>  
#include <tannic/c/types.h>

namespace tannic {   

enum class Kind { 
    Boolean,
    Natural,
    Integer,
    Real,
    Complex,
    Object
};

constexpr struct {
    std::string_view name;
    std::size_t      size; 
    std::uint8_t     bits;   
    Kind             kind;
}   

traits[TYPES] = {

    [boolean] = {
        .name = "boolean",
        .size = sizeof(std::uint8_t),
        .bits = 8,
        .kind = Kind::Boolean
    },

    [uint8] = {
        .name = "uint8",
        .size = sizeof(std::uint8_t),
        .bits = 8,
        .kind = Kind::Natural
    },

    [uint16] = {
        .name = "uint16",
        .size = sizeof(std::uint16_t),
        .bits = 16,
        .kind = Kind::Natural
    },

    [uint32] = {
        .name = "uint32",
        .size = sizeof(std::uint32_t),
        .bits = 32,
        .kind = Kind::Natural
    },

    [uint64] = {
        .name = "uint64",
        .size = sizeof(std::uint64_t),
        .bits = 64,
        .kind = Kind::Natural
    },

    [int8] = {
        .name = "int8",
        .size = sizeof(std::int8_t),
        .bits = 8,
        .kind = Kind::Integer
    },

    [int16] = {
        .name = "int16",
        .size = sizeof(std::int16_t),
        .bits = 16,
        .kind = Kind::Integer
    },

    [int32] = {
        .name = "int32",
        .size = sizeof(std::int32_t),
        .bits = 32,
        .kind = Kind::Integer
    },

    [int64] = {
        .name = "int64",
        .size = sizeof(std::int64_t),
        .bits = 64,
        .kind = Kind::Integer
    },

    [float16] = {
        .name = "float16",
        .size = 2,
        .bits = 16,
        .kind = Kind::Real
    },

    [bfloat16] = {
        .name = "bfloat16",
        .size = 2,
        .bits = 16,
        .kind = Kind::Real
    },

    [float32] = {
        .name = "float32",
        .size = sizeof(float),
        .bits = 32,
        .kind = Kind::Real
    },

    [float64] = {
        .name = "float64",
        .size = sizeof(double),
        .bits = 64,
        .kind = Kind::Real
    },

    [complex64] = {
        .name = "complex64",
        .size = 2 * sizeof(float),
        .bits = 64,
        .kind = Kind::Complex
    },

    [complex128] = {
        .name = "complex128",
        .size = 2 * sizeof(double),
        .bits = 128,
        .kind = Kind::Complex
    },

    [object] = {
        .name = "object",
        .kind = Kind::Object
    },

    [any] = {
        .name = "any"
    },

    [unknown] = {
        .name = "unknown" 
    },
};  

template<Kind K, typename Tag>
struct Promotion {
    static constexpr auto operator()(type first, type second) -> type {
        return (traits[first].bits >= traits[second].bits) ? first : second;
    }
};

template<typename Tag>
struct Promotion<Kind::Complex, Tag> {
    static constexpr auto operator()(type first, type second) -> type {
        if (traits[first].bits == 128 || traits[second].bits == 128 || first == float64 || second == float64) 
            return complex128;
        return complex64;
    }
};

template<typename Tag>
struct Promotion<Kind::Real, Tag> {
    static constexpr auto operator()(type first, type second) -> type {
        if ((first == bfloat16 && second == float16) || (first == float16 && second == bfloat16)) return float32;
        if (traits[first].kind == Kind::Real && traits[second].kind != Kind::Real) return first;
        if (traits[second].kind == Kind::Real && traits[first].kind != Kind::Real) return second;
        return (traits[first].bits >= traits[second].bits) ? first : second;
    }
};

template<typename Tag>
struct Promotion<Kind::Integer, Tag> {
    static constexpr auto operator()(type first, type second) -> type {
        if (traits[first].kind == Kind::Natural || traits[second].kind == Kind::Natural) {
            type natural_t = (traits[first].kind == Kind::Natural) ? first : second;
            type integer_t = (traits[first].kind == Kind::Integer) ? first : second;

            if (traits[natural_t].bits < traits[integer_t].bits) return integer_t;
            
            auto max_bits = std::max(traits[first].bits, traits[second].bits);
            if (max_bits <= 8)  return int16;
            if (max_bits <= 16) return int32;
            return int64;
        } 
        return (traits[first].bits >= traits[second].bits) ? first : second;
    }
};

template<typename Tag>
constexpr auto promote(type first, type second) -> type {
    if (first == second) return first; 
    Kind kind = std::max(traits[first].kind, traits[second].kind);
    switch (kind) {
        case Kind::Complex: return Promotion<Kind::Complex, Tag>{}(first, second);
        case Kind::Real:    return Promotion<Kind::Real,    Tag>{}(first, second);
        case Kind::Integer: return Promotion<Kind::Integer, Tag>{}(first, second);
        case Kind::Natural: return Promotion<Kind::Natural, Tag>{}(first, second);
        case Kind::Boolean: return Promotion<Kind::Boolean, Tag>{}(first, second);
        default:            return unknown;
    }
};

class Type { 
public: 
    constexpr Type() noexcept
    :   type_(unknown) {}

    constexpr Type(type type) noexcept 
    :   type_(type) {}
  
    constexpr operator type() const {
        return type_;
    }
    
    [[nodiscard]] constexpr auto id() const noexcept -> int {
        return static_cast<int>(type_);
    }

    [[nodiscard]] constexpr auto name() const noexcept ->  std::string_view  {
        return traits[type_].name;
    }

    [[nodiscard]] constexpr auto size() const noexcept -> std::size_t {
        return traits[type_].size;
    }

    [[nodiscard]] constexpr auto bits() const noexcept -> std::uint8_t  {
        return traits[type_].bits;
    } 

    [[nodiscard]] constexpr auto kind() const noexcept -> Kind {
        return traits[type_].kind;
    }
 
    template<typename Tag = void, typename... Types>
    [[nodiscard]] static constexpr auto infer(Type first, Types... rest) -> Type { 
        type result = first;
        ((result = promote<Tag>(result, rest)), ...);
        return Type(result);
    }
    
private:
    type type_;
}; 
 
auto operator<<(std::ostream&, Type type) -> std::ostream&; 

} 

#endif 