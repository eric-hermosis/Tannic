
#ifndef SCHEDULERS_HPP_0x45524943
#define SCHEDULERS_HPP_0x45524943

#include <iostream>

#include <vector>
#include <memory>
#include <tannic/visitors.hpp>
#include <tannic/expressions.hpp>
#include <tannic/variables.hpp>
#include <tannic/types.hpp>
#include <tannic/handlers.hpp>

namespace tannic {

using expressions::Index;
using expressions::Expression;
using expressions::Variable;
using expressions::Describable;
 
class Scheduler {
public:  
    Scheduler(std::size_t size); 
    ~Scheduler();
    Scheduler(Scheduler const& other) = delete;
    Scheduler(Scheduler && other) noexcept = default;
    Scheduler& operator=(Scheduler const& other) = delete;
    Scheduler& operator=(Scheduler && other) noexcept = default;
 
    void transverse(Variable const& variable) { 
        if (visitor_->visited(variable.index())) { 
            return; 
        }  
    }
    
    template<class Symbol, class ... Expressions>
    void transverse(Expression<Symbol, Expressions...> const& expression) {    
        if (visitor_->visited(expression.index())) { 
            return;
        }

        else { 
            Type types[sizeof...(Expressions)];
            
            template for (auto index = 0; auto const& source : expression.sources()) {
                transverse(source);

                if constexpr (Describable<decltype(source)>) {
                    types[index++] = source.type();
                } 

                else {
                    types[index++] = unknown;
                } 
            }
            
            auto handler = handlers_.get(expression.symbol(), types);
            
            visitor_->visit(expression.index());  
        } 
    }

private:
    Handlers handlers_;
    std::unique_ptr<Visitor> visitor_ = nullptr;
};

}

#endif