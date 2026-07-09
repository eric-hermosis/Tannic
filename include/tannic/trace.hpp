#include <cstdint>
#include <vector>

#include <tannic/types.hpp>

namespace tannic::expression {

class Node {
public:
    Node();
    ~Node();

    static auto allocate() -> Node*;
    void set(Type const& type) noexcept ;
    void link(Node* source) noexcept ;
    void acquire() noexcept;
    void release() noexcept;
    void prune() noexcept;

private:
    std::uint32_t links_;
    std::vector<Node*> sources_;
};

} namespace tannic::execution {

class Node {
public:
    Node();
    ~Node();

    static auto allocate() -> Node*;
    void link(Node* source) noexcept;
    void acquire() noexcept;
    void release() noexcept;
    void prune() noexcept;

private:
    std::uint32_t links_;
    std::vector<Node*> sources_;
};

class Nodes {
public:
    Nodes(std::size_t count);
    void resize(std::size_t count) noexcept ;
    void set(std::size_t index, Node*) noexcept ;
    auto get(std::size_t index) noexcept -> Node*;
    bool has(std::size_t index) noexcept;
    void clear() noexcept;

private:
    std::vector<Node*> list_;
};

}