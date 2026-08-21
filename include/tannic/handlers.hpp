// Copyright 2026 Eric Hermosis
//
// This file is part of the Blazar Tensor Library.
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
#ifndef HANDLERS_HPP_0x45524943 
#define HANDLERS_HPP_0x45524943 

#include <tannic/types.hpp> 

namespace tannic { 

class Handler {};
  
class Handlers {
public: 
    template<typename Symbol, typename... Types>
    auto get(Symbol, Types const&... types) const -> Handler;

    template<typename Symbol, auto Arity>
    auto get(Symbol symbol, Type const (&types)[Arity]) const -> Handler { 
        return [&]<std::size_t... Index>(std::index_sequence<Index...>) {
            return Handlers::get(symbol ,types[Index]...);
        }(std::make_index_sequence<Arity>{});
    }
};
    
}

#endif