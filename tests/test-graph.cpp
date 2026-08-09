#include <gtest/gtest.h>
#include <tannic/graph.hpp>

using namespace tannic;

TEST(TestGraph, TestConstruction) { 

    Graph::preallocate(6);

    Node* x = Graph::allocate(Scope::Local);
    Node* y = Graph::allocate(Scope::Local);
    Node* z = Graph::allocate(Scope::Local);

    EXPECT_EQ(Graph::capacity(), 6);
    EXPECT_EQ(Graph::free(), 3);

    Node* xy = Graph::allocate(Scope::Local); xy->link(x); xy->link(y);
    Node* yz = Graph::allocate(Scope::Local); yz->link(y); yz->link(z);
    Node* zx = Graph::allocate(Scope::Local); zx->link(z); zx->link(x);

    EXPECT_EQ(Graph::capacity(), 6);
    EXPECT_EQ(Graph::free(), 0);

    Node* xyyz = Graph::allocate(Scope::Local); xyyz->link(xy); xyyz->link(yz);
    Node* xyyzzx = Graph::allocate(Scope::Local); xyyzzx->link(xyyz); xyyzzx->link(zx);
 
    EXPECT_EQ(Graph::capacity(), 8);
    EXPECT_EQ(Graph::free(), 0);

    xyyzzx->acquire();
    xyyzzx->release(); 

    EXPECT_EQ(Graph::capacity(), 8);
    EXPECT_EQ(Graph::free(), 8);
} 