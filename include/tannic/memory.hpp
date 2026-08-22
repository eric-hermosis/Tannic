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
#ifndef MEMORY_HPP_0x45524943
#define MEMORY_HPP_0x45524943
#include <cstdint>
#include <cstddef>
#include <vector>

namespace tannic {
 
class Environment;

class Memory { 
public:  
    using Body = struct allocation_t; 
    Memory();
    void bump() noexcept;
    bool dump() noexcept;
    void acquire() noexcept;
    void release() noexcept; 
    void set(std::size_t size, Environment const& environment) noexcept;  
    void reset() noexcept; 
    void allocate();
    void deallocate() noexcept;
    auto body() const noexcept -> Body*;
    
private: 
    Body* body_ = nullptr;  
    std::uint32_t references_;
};  
  
}

#endif