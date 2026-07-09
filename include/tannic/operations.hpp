#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP
    
#include <tannic/types.hpp> 
#include <tannic/expressions.hpp>

namespace tannic::expressions {
  
template<class Operator, Composable... Operands>
class Operation : public Expression<Operator, Operands...>{
public:  
    constexpr Operation(Operands const&... operands)
    :   Expression<Operator, Operands...>({}, operands...) {  
        type_ = Type::infer(this->symbol, operands.type()...); 
    } 

    [[nodiscard]] constexpr auto type() const -> Type const& {
        return type_;
    }

private:
    Type type_;     
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
constexpr auto operator-(Operand && operand) {
    return Operation<Negation, Operand>(std::forward<Operand>(operand));
}

template<Composable Augend, Composable Addend>
constexpr auto operator+(Augend && augend, Addend && addend) {
    return Operation<Addition, Augend, Addend>(std::forward<Augend>(augend), std::forward<Addend>(addend));
}

template<Composable Dividend, Composable Divisor>
constexpr auto operator/(Dividend && dividend, Divisor && divisor) {
    return Operation<Division, Dividend, Divisor>(std::forward<Dividend>(dividend), std::forward<Divisor>(divisor));
}

template<Composable Minuend, Composable Subtrahend>
constexpr auto operator-(Minuend && minuend, Subtrahend && subtrahend) {
    return Operation<Subtraction, Minuend, Subtrahend>(std::forward<Minuend>(minuend), std::forward<Subtrahend>(subtrahend));
}

template<Composable Multiplicand, Composable Multiplier>
constexpr auto operator*(Multiplicand && multiplicand, Multiplier && multiplier) {
    return Operation<Multiplication, Multiplicand, Multiplier>(std::forward<Multiplicand>(multiplicand), std::forward<Multiplier>(multiplier));
}

template<Composable Base, Composable Exponent>
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