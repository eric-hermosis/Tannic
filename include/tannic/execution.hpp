#ifndef EXECUTION_HPP
#define EXECUTION_HPP

#include <iostream>
#include <tuple>
#include <memory>

namespace tannic::execution {

class Node;
class Nodes;

class Handle {
public:     
    Handle();

private:
    friend class Handles;
    Handle(Node* node);
    Node* node_ = nullptr; 
};

class Handles {
public:
    using Index = std::size_t;
    Handles(std::size_t count);
    auto create(Index index) -> Handle; 
    void set(Index index, Handle const&);
    bool has(Index index);
    auto get(Index index) -> Handle;

private:
    std::unique_ptr<Nodes> nodes_;
};

}

#endif