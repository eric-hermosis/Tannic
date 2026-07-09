#ifndef ENVIRONMENTS_HPP
#define ENVIRONMENTS_HPP

#include <variant>

class Host {};

class Environment {
    public:

    Environment() = default;

    Environment(Host const& host) 
    :   domain_(host) {}

    private:
    std::variant<std::monostate, Host> domain_;
};

#endif