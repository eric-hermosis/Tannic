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
#ifndef OPERATIONS_HPP_0x45524943
#define OPERATIONS_HPP_0x45524943 

#include <tannic/types.hpp>
#include <tannic/layouts.hpp>
#include <tannic/expressions.hpp>

namespace tannic::expressions {
  
template<class Operator, class... Operands>
class Operation : public Expression<Operator, Operands...>{
public:  
    constexpr Operation(Operands const&... operands)
    :   Expression<Operator, Operands...>({}, operands...),
        type_(Type::infer<Operator>(operands.type()...)),
        layout_(Layout::infer<Operator>(operands.layout()...))
    {} 

    [[nodiscard]] constexpr auto type() const -> Type const& {
        return type_;
    }

    [[nodiscard]] constexpr auto layout() const -> Layout const& {
        return layout_;
    }

private:
    Type type_;    
    Layout layout_; 
};
 
} namespace tannic::operations {   
 
struct Negation {};
struct Addition {};
struct Division {};
struct Subtraction{}; 
struct Multiplication {}; 
struct Exponentiation {};

} namespace tannic::operators {

using namespace operations; 
using namespace expressions;

template<class Operand>
constexpr auto operator-(Operand && operand) {
    return Operation<Negation, Operand>(std::forward<Operand>(operand));
}

template<class Augend, class Addend>
constexpr auto operator+(Augend && augend, Addend && addend) {
    return Operation<Addition, Augend, Addend>(std::forward<Augend>(augend), std::forward<Addend>(addend));
}

template<class Dividend, class Divisor>
constexpr auto operator/(Dividend && dividend, Divisor && divisor) {
    return Operation<Division, Dividend, Divisor>(std::forward<Dividend>(dividend), std::forward<Divisor>(divisor));
}

template<class Minuend, class Subtrahend>
constexpr auto operator-(Minuend && minuend, Subtrahend && subtrahend) {
    return Operation<Subtraction, Minuend, Subtrahend>(std::forward<Minuend>(minuend), std::forward<Subtrahend>(subtrahend));
}

template<class Multiplicand, class Multiplier>
constexpr auto operator*(Multiplicand && multiplicand, Multiplier && multiplier) {
    return Operation<Multiplication, Multiplicand, Multiplier>(std::forward<Multiplicand>(multiplicand), std::forward<Multiplier>(multiplier));
}

template<class Base, class Exponent>
constexpr auto operator^(Base && base, Exponent && exponent) {
    return Operation<Exponentiation, Base, Exponent>(std::forward<Base>(base), std::forward<Exponent>(exponent));
} 

} namespace tannic {

using operators::operator+;
using operators::operator-;
using operators::operator*;
using operators::operator/;
using operators::operator^;

}

#endif