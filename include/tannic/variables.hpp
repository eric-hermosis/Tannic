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

namespace tannic::expressions {

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

    constexpr auto operator=(Variable const& other) { 
        if !consteval { 
            copy(other); 
        } 
        return *this; 
    }

    constexpr auto operator=(Variable && other) noexcept {
        if !consteval { 
            move(other);  
        } 
        return *this; 
    }

    constexpr auto symbol(this auto && self) -> Symbol {
        return Symbol(self);
    }  
    
    auto forward() const -> Vertex const& {
        if(!vertex_) {
            vertex_ = Vertex(symbol()); 
        }
        vertex_.acquire(); 
        return vertex_;
    }

    void backward() const {
        if (vertex_) { 
            vertex_.release();
        }
    }

    void acquire() const noexcept;
    void release() const noexcept;

protected:
    void copy(Variable const& other) const;
    void move(Variable & other) const noexcept;

private:
    mutable Vertex vertex_;
};

}

#endif