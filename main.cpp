#include <iostream>
#include <vector>  
#include <stack>
#include <mutex>
#include <tannic/variables.hpp>
#include <tannic/operations.hpp>

using namespace tannic;
using expressions::Variable;

int main() {
    Variable x; x.acquire();
    Variable y; y.acquire();
    Variable z; z.acquire();

    {
        auto expr = x*y + y*z + z*x;
        auto w = expr.forward();

        std::cout << "1!" << std::endl;
        expr.backward();

        std::cout << "2" << std::endl;
    }

    x.release();
    y.release();
    z.release(); 
    std::cout << "3" << std::endl; 
    std::cout << "EXPR DESTROYED" << std::endl;
}