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
#ifndef VISITORS_HPP_0x45524943
#define VISITORS_HPP_0x45524943

#include <cstdint>
#include <cstddef>
#include <vector>

namespace tannic {  

class Visitor {
public: 
    void visit(std::size_t index) noexcept; 
    bool visited(std::size_t index) const noexcept;
    void set(std::size_t size); 
    void reset() noexcept;

private:
    std::size_t size_;
    std::uint64_t generation_ = 1;
    std::vector<std::uint64_t> visits_;
}; 

}

#endif