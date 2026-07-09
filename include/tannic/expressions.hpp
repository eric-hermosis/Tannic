#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP
  
#include <tuple>
#include <concepts>
#include <type_traits>
#include <tannic/types.hpp>
#include <tannic/execution.hpp>
#include <tannic/graph.hpp>

namespace tannic::expressions {

using execution::Handle;
using execution::Handles;
using expression::Vertex;
using expression::Vertices;

template<class Expression>
concept Composable = requires(Expression const& expression) {
    { expression.type() } -> std::same_as<Type const&>;
};

template<Composable Expression>
class Trait {
public:
    using type = typename std::decay<Expression>::type;
};

template<class Symbol, Composable ... Expressions>
class Expression {
public:
    using Index = std::size_t;
    std::decay<Symbol>::type symbol;
    std::tuple<typename Trait<Expressions>::type ...> sources;

    constexpr Expression(Symbol symbol, Expressions const& ... sources) 
    :   symbol(symbol)
    ,   sources(sources...) {}    

    template<typename Self>
    auto forward(this Self && self, Vertices& vertices) -> Vertex {
        if(!self.vertex_) {
            self.index_  = Index(vertices.count++);
            self.vertex_ = Vertex(self.type());   
            template for(auto const& source : self.sources_;) {
                self.vertex_.link(source.forward(vertices));
            }
        }
        return self.vertex_;
    }

    template<typename Self>
    auto forward(this Self && self, Handles& handles) -> Handle {
        if (handles.has(self.index_)) {
            return handles.get(self.index_);
        } 
        
        else {
            return std::apply([&](auto const& ... source) { 
                Handle handle = handles.create(self.index_);
                return handle;
            }, self.sources);
        } 
    }

private:
    mutable Index index_;
    mutable Vertex vertex_;
};

}

#endif