
#ifndef SCHEDULERS_HPP_0x45524943
#define SCHEDULERS_HPP_0x45524943

#include <iostream>

#include <vector>
#include <memory>
#include <tannic/visitors.hpp>
#include <tannic/expressions.hpp>
#include <tannic/variables.hpp>

namespace tannic {

using expressions::Index;
using expressions::Expression;
using expressions::Variable;
 
class Scheduler {
public:  
    Scheduler(std::size_t size); 
    ~Scheduler();
    Scheduler(Scheduler const& other) = delete;
    Scheduler(Scheduler && other) noexcept = delete;
    auto operator=(Scheduler const& other) = delete;
    auto operator=(Scheduler && other) = delete;
 
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
            template for (auto const& source : expression.sources()) {
                transverse(source);
            }

            visitor_->visit(expression.index());  
        } 
    }

private:
    std::unique_ptr<Visitor> visitor_ = nullptr;
};

}

#endif