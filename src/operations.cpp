#include <iostream>

#include <tannic/operations.hpp>
#include <tannic/handlers.hpp>

namespace tannic {

using operations::Negation;
using operations::Addition;
using operations::Division;
using operations::Subtraction;
using operations::Multiplication;
using operations::Exponentiation;
  
template<>
auto Handlers::get(Negation, Type const& type) const -> Handler { 
    return Handler{};
};

template<>
auto Handlers::get(Addition, Type const& first, Type const& second) const -> Handler { 
    return Handler{};
};

template<>
auto Handlers::get(Multiplication, Type const& first, Type const& second) const -> Handler { 
    return Handler{};
}; 

template<>
auto Handlers::get(Division, Type const& first, Type const& second) const -> Handler { 
    return Handler{};
};

template<>
auto Handlers::get(Subtraction, Type const& first, Type const& second) const -> Handler { 
    return Handler{};
};
  
}