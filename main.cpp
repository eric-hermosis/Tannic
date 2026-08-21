#include <tannic/variables.hpp>
#include <tannic/tensors.hpp>
#include <tannic/operations.hpp> 
#include <tannic/expressions.hpp> 
#include <tannic/schedules.hpp>

using namespace tannic;
using expressions::Variable;
using expressions::Graph; 

int main() { 
    Variable x; x.acquire();
    Variable y; y.acquire();
    Variable z; z.acquire(); 
    {    
        Graph graph(x*y + y*z + z*x); 
        Scheduler scheduler(graph.size(), Host());
        scheduler.transverse(graph.expression()); 
    } 
    
}