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

#include <iostream>
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
      
class Index {
public: 
    constexpr Index() = default;
    Index(std::size_t value); 
    operator bool() const noexcept;
    operator std::size_t() const noexcept;
    [[nodiscard]] auto value() const noexcept -> std::size_t;
    [[nodiscard]] auto forward() noexcept -> Index;

private:   
    std::size_t value_ = 0;
};
 
class Vertex {
public: 
    constexpr Vertex() = default;
    operator bool() const noexcept;
    bool operator==(Vertex const& other) const noexcept;
    
    void succeed(Vertex const& other); 
    void precede(Vertex const& other); 
       
    void acquire() noexcept;
    void release() noexcept; 
    void set(Symbol const& symbol, Type const& type, Layout const& layout) noexcept;

private: 
    Node* node_ = nullptr;
};   
   
template<class Expression>
concept Composable = requires(Expression const& expression, Index& index) {
    { expression.forward(index)  }; 
    { expression.backward()      };
    { expression.vertex()   } -> std::same_as<Vertex const&>;
    { expression.index()    } -> std::same_as<Index const&>;
};  

template<class Expression>
concept Describable = requires(Expression const& expression) {
    { expression.symbol() } -> std::convertible_to<Symbol>;
    { expression.type()   } -> std::same_as<Type const&>;
    { expression.layout() } -> std::same_as<Layout const&>;
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
    
    constexpr auto const& sources() const {
        return sources_;
    }        
 
    template<class Self>
    void forward(this Self&& self, Index& index) {  
        if(!self.vertex_) {   
            self.vertex_.acquire(); 
            self.vertex_.set(self.symbol(), self.type(), self.layout());
            template for (auto const& source : self.sources_) {
                source.forward(index);
                self.vertex_.succeed(source.vertex());
            }   
            self.index_ = index.forward(); 
        } 
    }
 
    template<class Self>
    void backward(this Self&& self) {
        if (self.vertex_) {  
            template for (auto const& source : self.sources_) {
                source.backward();
            }   
            self.index_ = 0;
            self.vertex_.release();  
        }
    }

    [[nodiscard]] auto index() const noexcept -> Index const& {
        return index_;
    }

    [[nodiscard]] auto vertex() const noexcept -> Vertex const& {
        return vertex_;
    }

private:   
    mutable Index index_;
    mutable Vertex vertex_;
    std::decay<Symbol>::type symbol_;
    std::tuple<typename Trait<Expressions>::type ...> sources_;  
}; 

template<Composable Expression>
class Graph {
public: 

    Graph(Expression && expression) 
    :   expression_(std::move(expression)) {
        expression_.forward(index_);
    }

    ~Graph() {
        expression_.backward();
    } 

    [[nodiscard]] auto expression() -> Expression const& {
        return expression_;
    }

    [[nodiscard]] auto root() const noexcept -> Vertex const& {
        return expression_.vertex();
    }

    [[nodiscard]] auto size() const noexcept -> std::size_t {
        return index_.value();
    } 

private:
    Index index_;
    Expression expression_;
};
   
} namespace tannic {

using expressions::Graph;

}

#endif