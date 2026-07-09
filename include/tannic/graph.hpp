#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <tannic/types.hpp>

namespace tannic::expression {

class Node; 
 
class Vertex {
public:
    constexpr Vertex() = default;

    constexpr ~Vertex() {
        if !consteval {
            release();
        }
    }

    constexpr Vertex(Vertex const& other) {
        if !consteval {
            copy(other);
        }
    }

    constexpr Vertex(Vertex && other) noexcept {
        if !consteval {
            move(other);
        }
    }

    constexpr auto operator=(Vertex const& other) -> Vertex& {
        if !consteval {
            copy(other);
            return *this;
        }
    }

    constexpr auto operator=(Vertex && other) noexcept -> Vertex& {
        if !consteval {
            move(other);
            return *this;
        }
    }

    constexpr operator bool() const noexcept {
        return node_ ? true : false;
    }

    Vertex(Type const& type);
    void move(Vertex& other) noexcept;
    void copy(Vertex const& other); 
    void link(Vertex const& other); 
    void release();
    void prune();

private:
    Node* node_ = nullptr;
};   

class Vertices {
    std::size_t count = 0;
};

}

#endif