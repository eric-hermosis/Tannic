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
    :   Expression<Operator, Operands...>({}, operands...) { 
        
        if constexpr ((Describable<Operands> && ...)) {
            type_ = Type::infer<Operator>(operands.type()...); 
            layout_ = Layout::infer<Operator>(operands.layout()...);
        }
    } 

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

template<Composable Operand>
constexpr auto operator-(Operand const& operand) {
    return Operation<Negation, Operand>(operand);
}

template<Composable Augend, Composable Addend>
constexpr auto operator+(Augend const& augend, Addend const& addend) {
    return Operation<Addition, Augend, Addend>(augend, addend);
}

template<Composable Dividend, Composable Divisor>
constexpr auto operator/(Dividend const& dividend, Divisor const& divisor) {
    return Operation<Division, Dividend, Divisor>(dividend, divisor);
}

template<Composable Minuend, Composable Subtrahend>
constexpr auto operator-(Minuend const& minuend, Subtrahend const& subtrahend) {
    return Operation<Subtraction, Minuend, Subtrahend>(minuend, subtrahend);
}

template<Composable Multiplicand, Composable Multiplier>
constexpr auto operator*(Multiplicand const& multiplicand, Multiplier const& multiplier) {
    return Operation<Multiplication, Multiplicand, Multiplier>(multiplicand, multiplier);
}

template<Composable Base, Composable Exponent>
constexpr auto operator^(Base const& base, Exponent const& exponent) {
    return Operation<Exponentiation, Base, Exponent>(base, exponent);
}

} namespace tannic {

using operators::operator+;
using operators::operator-;
using operators::operator*;
using operators::operator/;
using operators::operator^;

}

#endif