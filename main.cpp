#include <iostream>
#include <utility>
#include <tannic/tensors.hpp>
#include <tannic/operations.hpp>
#include <tannic/graph.hpp>

using namespace tannic;


class Context {
    using Index = std::size_t;

    void set(Index, Scope, Type);
    void set(Index, Scope, Layout); 
};

int main() {
    
}