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
#include <concepts>
#include <type_traits>  

namespace tannic {

class Node;
class Type;
class Layout;
class Symbol; 

} namespace tannic::expressions {
 
template<class Expression>
class Trait {
public:
    using type = typename std::decay<Expression>::type;
};
 
class Vertex {
public:
    constexpr Vertex() = default;

    Vertex(Symbol const& symbol);
    operator bool() noexcept;
    bool operator==(Vertex const& other) const noexcept;
    
    void succeed(Vertex const& other); 
    void precede(Vertex const& other);
      
    void acquire() noexcept;
    void release() noexcept;
    
private: 
    Node* node_ = nullptr;
};
  
template<class Expression>
concept Composable = requires(Expression const& expression) {
    { expression.forward()  } -> std::same_as<Vertex const&>; 
    { expression.backward() };
};  
      
template<class Symbol, class ... Expressions>
class Expression {
public:  

    constexpr Expression(Symbol symbol, Expressions const& ... sources) 
    :   symbol_(symbol)
    ,   sources_(sources...) {} 

    constexpr auto symbol() const -> Symbol const& {
        return symbol_;
    }  

    auto forward() const -> Vertex const& {
        if(!vertex_) {
            vertex_ = Vertex(symbol());
            vertex_.acquire();
            template for (auto const& source : sources_) {
                vertex_.succeed(source.forward());
            }
        }
        return vertex_;
    }

    void backward() const {
        if (vertex_) { 
            template for (auto const& source : sources_) {
                source.backward();
            } 
            vertex_.release();
        }
    }

private:  
    mutable Vertex vertex_;
    std::decay<Symbol>::type symbol_;
    std::tuple<typename Trait<Expressions>::type ...> sources_;  
};

}   

#endif