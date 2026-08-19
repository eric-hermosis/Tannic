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
#ifndef TENSORS_HPP_0x45524943
#define TENSORS_HPP_0x45524943

#include <tannic/types.hpp>
#include <tannic/layouts.hpp>
#include <tannic/symbols.hpp>   
#include <tannic/expressions.hpp> 
#include <tannic/variables.hpp>

namespace tannic::expressions {

class Tensor : public Variable {
public: 
    constexpr Tensor() 
    :   type_(unknown) {}

    constexpr Tensor(Type const& type)
    :   type_(type) {}

    constexpr Tensor(Type const& type, Shape const& shape)
    :   type_(type)
    ,   layout_(shape) {}

    constexpr Tensor(Type const& type, Shape const& shape, Strides const& strides)
    :   type_(type)
    ,   layout_(shape, strides) {} 

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

template<>
class Trait<Tensor> {
public:
    using type = Tensor const&;
};

} namespace tannic {

using expressions::Tensor;

}

#endif