#ifndef TENSORS_HPP
#define TENSORS_HPP

#include <tannic/types.hpp> 
#include <tannic/execution.hpp>

namespace tannic::expression {

using execution::Handle;
using execution::Handles;

class Tensor {
public:

    constexpr Tensor(Type const& type) 
    :   type_(type) {}

    constexpr auto type() const -> Type const& {
        return type_;
    }

    auto forward(Handles& handles) const -> Handle {
        return Handle();
    }

private:
    Type type_; 
};

} namespace tannic {

using expression::Tensor;

}

#endif