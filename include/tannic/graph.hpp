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
#ifndef GRAPH_HPP_0x45524943
#define GRAPH_HPP_0x45524943

#include <cstdint>
#include <cstddef>
#include <mutex>
#include <stack>
#include <vector>
#include <tannic/context.hpp>

namespace tannic {

class Node {
public:
    using Index = std::size_t;
    Node(Index index, Scope scope);

    [[nodiscard]] auto index() const noexcept -> Index;
    [[nodiscard]] auto scope() const noexcept -> Scope;

    void acquire() noexcept;
    void release() noexcept;
    void link(Node* source) noexcept;
    void prune() noexcept;

private:
    Index index_;
    Scope scope_;
    std::uint32_t links_ = 0;
    std::vector<Node*> priors_;
};

class Graph {
public:
    static void preallocate(std::size_t count);
    [[nodiscard]] static auto allocate(Context context) -> Node*;
    [[nodiscard]] static auto capacity() -> std::size_t;
    [[nodiscard]] static auto available() -> std::size_t;
};

}

#endif