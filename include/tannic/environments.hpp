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

#ifndef ENVIRONMENTS_HPP_0x45524943 
#define ENVIRONMENTS_HPP_0x45524943  
 
#include <variant>   
#include <string_view>

namespace tannic { 
 
class Host {};  
class Device {};

class Environment {
    public: 
    Environment() = default; 
    Environment(Host const& host);
    Environment(Device const& device);
    operator bool() const noexcept;

    private:
    std::variant<std::monostate, Host, Device> domain_;
};

} 

#endif