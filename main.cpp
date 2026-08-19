#include <tannic/variables.hpp>
#include <tannic/tensors.hpp>
#include <tannic/operations.hpp> 

using namespace tannic;
using expressions::Vertex;
using expressions::Index;
using expressions::Variable;
using expressions::Expression;

int main() { 
    Variable x; x.acquire();
    Variable y; y.acquire();
    Variable z; z.acquire(); 
    { 
        Index index;
        auto expr = x*y + y*z + z*x; 
        auto source = expr.forward(index);     
        expr.backward(); 
    } 
    
}


/*
#include <iostream>
#include <vector>  
#include <stack>
#include <iostream>
#include <unordered_set>
#include <mutex>
#include <tannic/variables.hpp>
#include <tannic/tensors.hpp>
#include <tannic/operations.hpp> 
#include <iostream>
#include <unordered_set>
#include <typeinfo>

using namespace tannic;
using expressions::Vertex;
using expressions::Variable;
using expressions::Expression;
 
void traverse(Variable const& var, std::unordered_set<int>& visited) {
    int id = var.forward().index(); 

    if (visited.contains(id)) return;
    visited.insert(id);

    std::cout << "Variable Vertex [" << id << "]\n";
}

template <class Symbol, class... Expressions>
void traverse(Expression<Symbol, Expressions...> const& expr, std::unordered_set<int>& visited) {
    int id = expr.forward().index(); 

    if (visited.contains(id)) return;
    visited.insert(id);

    // Traverse the sources recursively
    template for (auto const& source : expr.sources()) {
        traverse(source, visited);
    }
    
    // Because we accepted an Expression, we know exactly what Symbol is!
    std::cout << "Expression Vertex [" << id << "] "
              << "| Symbol Type: " << typeid(Symbol).name() << " "
              << "-> Sources: ";
              
    template for (auto const& source : expr.sources()) {
        std::cout << source.forward().index() << " ";
    }
    std::cout << "\n";
}

int main() {
    Variable x; x.acquire();
    Variable y; y.acquire();
    Variable z; z.acquire(); 
    
    auto expr = x*y + y*z + z*x; 
    auto source = expr.forward();  
 
    std::cout << "--- Computation Graph ---\n";
    std::unordered_set<int> visited;
     
    traverse(expr, visited);
    
    std::cout << "-------------------------\n";

    expr.backward();
    
    return 0;
}  

*/