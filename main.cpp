#include <tannic/variables.hpp>
#include <tannic/tensors.hpp>
#include <tannic/operations.hpp> 
#include <tannic/expressions.hpp> 
#include <tannic/schedules.hpp>

using namespace tannic;
using expressions::Vertex;
using expressions::Index;
using expressions::Variable;
using expressions::Expression;
using expressions::Composable;


int main() { 
    Variable x; x.acquire();
    Variable y; y.acquire();
    Variable z; z.acquire();
  
    { 
        Index index = 0;
        auto expr = x*y + y*z + z*x; 
        auto source = expr.forward(index);        
        Scheduler sched(index.value());
        sched.transverse(expr);
        expr.backward(); 
    } 
    
}