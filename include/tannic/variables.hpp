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

#ifndef VARIABLES_HPP_0x45524943
#define VARIABLES_HPP_0x45524943
 
#include <tannic/symbols.hpp>  
#include <tannic/expressions.hpp>
 
namespace tannic {

using expressions::Describable;

class Variable {
public:
    constexpr Variable() = default;

    constexpr ~Variable() { 
        if !consteval { 
            release(); 
        } 
    }

    constexpr Variable(Variable const& other) { 
        if !consteval { 
            copy(other); 
        } 
    }

    constexpr Variable(Variable && other) noexcept { 
        if !consteval { 
            move(other); 
        } 
    }

    constexpr Variable& operator=(Variable const& other) { 
        if !consteval { 
            copy(other); 
        } 
        return *this; 
    }

    constexpr Variable& operator=(Variable && other) noexcept {
        if !consteval { 
            move(other);  
        } 
        return *this; 
    } 

    constexpr auto symbol(this auto && self, auto& index) -> Symbol {
        return Symbol(self);
    }  
 
    template<class Self>
    auto forward(this Self&& self, Index& index) { 
        if(!self.vertex_) {
            self.vertex_.acquire();
            if constexpr (Describable<Self>) {
                self.vertex_.set(self.symbol(), self.type(), self.layout());    
            }
        }  
 
        if(!self.index_) { 
            self.index_ = index.forward(); 
        }  
        
        self.vertex_.acquire(); 
    }
 
    template<class Self>
    void backward(this Self&& self) {  
        if (self.index_) {
            self.index_ = 0;
        }

        if (self.vertex_) {
            self.vertex_.release(); 
        } 
    }

    template<class Self>
    void acquire(this Self&& self) {
        if(!self.vertex_) {
            self.vertex_.acquire();
            if constexpr (Describable<Self>) {
                self.vertex_.set(self.symbol(), self.type(), self.layout());    
            }
        }  
    }

    template<class Self>
    void release(this Self&& self) { 
        if (self.vertex_) { 
            self.vertex_.release();
        } 
    }

    [[nodiscard]] auto index() const noexcept -> Index const&;
    [[nodiscard]] auto vertex() const noexcept -> Vertex const&;

protected:
    void copy(Variable const& other) const;
    void move(Variable & other) const noexcept;

private:
    mutable Index index_;
    mutable Vertex vertex_;
};

}

#endif