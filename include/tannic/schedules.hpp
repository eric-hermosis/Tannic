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

#ifndef SCHEDULES_HPP_0x45524943
#define SCHEDULES_HPP_0x45524943 

#include <vector>
#include <memory>
#include <tannic/visitors.hpp>
#include <tannic/expressions.hpp>
#include <tannic/variables.hpp>
#include <tannic/types.hpp>
#include <tannic/handlers.hpp>
#include <tannic/environments.hpp>

namespace tannic {
 
using expressions::Expression; 
using expressions::Describable;
 
class Schedule {
public: 
    
};

class Scheduler {
public:  
    Scheduler(std::size_t size, Environment const& environment); 
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
                    types[index] = source.type();
                }  
                index++;
            }
            
            auto handler = handlers_.get(expression.symbol(), types); 
            visitor_-> visit(expression.index());  
        } 
    }

private:
    Environment environment_;
    Handlers handlers_;
    std::unique_ptr<Visitor> visitor_ = nullptr;
};

}

#endif