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
#ifndef FUNCTIONS_HPP_0x45524943 
#define FUNCTIONS_HPP_0x45524943 

#include <tannic/types.hpp>
#include <tannic/layouts.hpp>
#include <tannic/expressions.hpp>

namespace tannic::expressions { 

template<class Functor, class... Arguments>
class Function : public Expression<Functor, Arguments...> {
public:   
    constexpr Function(Functor functor, Arguments const&... arguments)
    :   Expression<Functor, Arguments...>(functor, arguments...) {
        
        if constexpr ((requires { arguments.type(); } && ...)) {
            type_ = Type::infer<Functor>(arguments.type()...);
        }

        if constexpr ((requires { arguments.layout(); } && ...)) {
            layout_ = Layout::infer<Functor>(arguments.layout()...);
        }
    }

    [[nodiscard]] constexpr auto type() const -> Type const& {
        return type_;
    }

    [[nodiscard]] constexpr auto layout() const -> Layout const& {
        return layout;
    }

private:
    Type type_;    
    Layout layout_; 
}; 

} namespace tannic::functions {
    
struct Log {}; 
struct Exp {};
struct Sqrt {};
struct Rsqrt {};
struct Abs {};
struct Sin {};
struct Cos {};
struct Tan {};
struct Sinh {};
struct Cosh {};
struct Tanh {};
 
} namespace tannic::operators {

using namespace expressions; 
using namespace functions;

template<class Argument>
constexpr auto log(Argument&& argument) {
    return Function<Log, Argument>({}, std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto exp(Argument&& argument) {
    return Function<Exp, Argument>({}, std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto sqrt(Argument&& argument) {
    return Function<Sqrt, Argument>({}, std::forward<Argument>(argument));
}  

template<class Argument>
constexpr auto rsqrt(Argument&& argument) {
    return Function<Rsqrt, Argument>(std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto abs(Argument&& argument) {
    return Function<Abs, Argument>({}, std::forward<Argument>(argument));
}

template<class Argument>
constexpr auto sin(Argument&& argument) {
    return Function<Sin, Argument>({}, std::forward<Argument>(argument));
} 

template<class Argument>
constexpr auto cos(Argument&& argument) {
    return Function<Cos, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto tan(Argument&& argument) {
    return Function<Tan, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto sinh(Argument&& argument) {
    return Function<Sinh, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto cosh(Argument&& argument) {
    return Function<Cosh, Argument>({}, std::forward<Argument>(argument));
}
 
template<class Argument>
constexpr auto tanh(Argument&& argument) {
    return Function<Tanh, Argument>({}, std::forward<Argument>(argument));
}

} namespace tannic {
    
using operators::log;
using operators::exp;
using operators::sqrt;
using operators::rsqrt;
using operators::abs;
using operators::sin;
using operators::cos;
using operators::tan;
using operators::sinh;
using operators::cosh;
using operators::tanh;

} 

#endif