#include <iostream>
#include <tannic/tensors.hpp>
#include <tannic/operations.hpp>

using namespace tannic;

int main() {           
    {
        Tensor x;
        Tensor y;
        Tensor z;
        Tensor w = x*y + y*z + z*x;
    }
    
    std::cout << Graph::capacity() << std::endl;
    std::cout << Graph::available() << std::endl;
} 