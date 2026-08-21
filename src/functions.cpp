#include <tannic/handlers.hpp> 
#include <tannic/functions.hpp> 

namespace tannic {

using functions::Log;
using functions::Exp;
using functions::Sqrt;
using functions::Rsqrt;
using functions::Abs;
using functions::Sin;
using functions::Cos;
using functions::Tan;
using functions::Sinh;
using functions::Cosh;
using functions::Tanh;

template<>
auto Handlers::get(Log, Type const& type) const -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Exp, Type const& type) const -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Sqrt, Type const& type) const-> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Rsqrt, Type const& type) const -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Abs, Type const& type) const -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Sin, Type const& type) const -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Cos, Type const& type) const -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Tan, Type const& type) const -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Sinh, Type const& type) const -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Cosh, Type const& type) const -> Handler {
    return Handler{};
}

template<>
auto Handlers::get(Tanh, Type const& type) const -> Handler {
    return Handler{};
}

}