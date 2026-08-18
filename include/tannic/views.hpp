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
#ifndef VIEWS_HPP_0x45524943
#define VIEWS_HPP_0x45524943
 
#include <tannic/types.hpp>
#include <tannic/layouts.hpp>
#include <tannic/expressions.hpp>

namespace tannic::expressions { 

struct Slice {};

template<class Symbol, class Source> class View;
  
template<class Source>
class View<Slice, Source> : public Expression<Slice, Source> {
public:  
    template<class ... Indexes>
    constexpr View(Source const& source, Indexes ... indexes) 
    :   Expression<Slice, Source>({}, source) {  
        
        if constexpr (Typed<Source>) {
            type_ = source.type();
        }

        if constexpr (Ranked<Source>) {
            auto dimension = 0;    
            auto offset = source.layout().offset();

            Shape shape;
            Strides strides;

            template for (auto const& argument: std::make_tuple(indexes...)) {
                using Argument = std::decay_t<decltype(argument)>; 

                if constexpr (std::is_same_v<Argument, range_type>) { 
                    auto range = layouts::normalize(argument, source.layout().size(dimension));
                    auto size = range.stop - range.start; 
                    shape.append(size);
                    strides.append(source.layout().stride(dimension)); 
                    offset += range.start * source.layout().stride(dimension); 
                    dimension++;
                } 
                
                else if constexpr (std::is_integral_v<Argument>) { 
                    auto index = layouts::normalize(argument, source.layout().size(dimension));
                    offset += index * source.layout().stride(dimension);
                    dimension++;
                }

                else {         
                    throw Exception("Invalid index type"); 
                }  
            }
    
            while (dimension < source.layout().rank()) {
                shape.append(source.layout().size(dimension));
                strides.append(source.layout().stride(dimension));
                dimension++;
            } 
    
            layout_ = Layout(shape, strides, offset);
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

class Viewable {
public:
    template<typename Self>
    constexpr auto operator[](this Self&& self, index_type index) {
        return View<Slice, Self>(self, index);
    }

    template<typename Self>
    constexpr auto operator[](this Self&& self, range_type range) {
        return View<Slice, Self>(self, range);
    } 

    template<typename Self, class ... Arguments> 
    requires (sizeof...(Arguments) > 0) && (... && (std::integral<Arguments> || std::convertible_to<std::decay_t<Arguments>, range_type>))
    constexpr auto operator[](this Self&& self, Arguments... arguments) {
        return View<Slice, Self>(self, arguments...);
    }  
};

}

#endif