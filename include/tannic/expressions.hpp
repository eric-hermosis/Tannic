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
#ifndef EXPRESSIONS_HPP_0x45524943
#define EXPRESSIONS_HPP_0x45524943
 
#include <tuple> 
#include <type_traits> 
#include <tannic/context.hpp>
#include <tannic/graph.hpp>

namespace tannic {
  
class Type;
class Layout;
  
} namespace tannic::expressions {
    
template<class Expression>
concept Composable = requires(Expression const& expression) {
    { expression.type()   } -> std::same_as<Type const&>;
    { expression.layout() } -> std::same_as<Layout const&>;
};  

template<class Expression>
class Trait {
public:
    using type = typename std::decay<Expression>::type;
};
 
template<class Symbol, class ... Expressions>
class Expression {
public: 
    constexpr Expression(Symbol symbol, Expressions const& ... sources) 
    :   symbol_(symbol)
    ,   sources_(sources...) {} 

    constexpr auto symbol() -> Symbol const& {
        return symbol_;
    }

    template<typename Self>
    auto forward(this Self&& self, Context context) -> Node* {
        if(!self.node_) {
            self.node_ = Graph::allocate(context);    
            template for (auto const& source : self.sources_) {
                auto node = source.forward(context);
                self.node_->link(node);
            }
        }
        return self.node_;
    }

private:
    mutable Node* node_ = nullptr;
    std::decay<Symbol>::type symbol_;
    std::tuple<typename Trait<Expressions>::type ...> sources_;  
};

}   

#endif