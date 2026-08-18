#include <iostream>
#include <vector>  
#include <stack>
#include <mutex>
#include <tannic/tensors.hpp>
#include <tannic/operations.hpp>
 
using namespace tannic;
using expressions::Variable;

int main() {
    Variable x; x.acquire();
    Variable y; y.acquire();
    Variable z; z.acquire();
    auto expr = x*y + y*z + z*x;
    auto vertex = expr.forward(); 
    expr.backward();
}