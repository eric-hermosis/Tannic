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
#ifndef GRAPHS_HPP_0x45524943
#define GRAPHS_HPP_0x45524943

#include <cstdint>
#include <cstddef>
#include <vector>

namespace tannic {  

class Symbol;
class Layout;
class Type;  
class Handler;

class Node { 

public:  
    using Body = struct node_t; 
    Node();
    void bump();
    bool dump();
    void link(Node* other);
    void prune();
    void acquire() noexcept;
    void set(Symbol const& symbol, Type const& type, Layout const& layout) noexcept; 
    void set(Handler const& handler) noexcept;
    void reset() noexcept;
    void release() noexcept; 
    
private: 
    Body* body_ = nullptr;

    std::uint32_t links_;
    std::vector<Node*> sources_; 
}; 

}

#endif