#include <gtest/gtest.h>

/*
#include <tannic/graph.hpp>
#include <tannic/context.hpp>

using namespace tannic;

TEST(TestGraph, TestConstruction) { 
    Graph::preallocate(6);
    Context context(Scope::Local);

    Node* x = Graph::get(context);
    Node* y = Graph::get(context);
    Node* z = Graph::get(context);

    EXPECT_EQ(Graph::capacity(), 6);
    EXPECT_EQ(Graph::available(), 3);

    Node* xy = Graph::get(context); xy->link(x); xy->link(y);
    Node* yz = Graph::get(context); yz->link(y); yz->link(z);
    Node* zx = Graph::get(context); zx->link(z); zx->link(x);

    EXPECT_EQ(Graph::capacity(), 6);
    EXPECT_EQ(Graph::available(), 0);

    Node* xyyz = Graph::get(context); xyyz->link(xy); xyyz->link(yz);
    Node* xyyzzx = Graph::get(context); xyyzzx->link(xyyz); xyyzzx->link(zx);
 
    EXPECT_EQ(Graph::capacity(), 8);
    EXPECT_EQ(Graph::available(), 0);

    xyyzzx->acquire();
    xyyzzx->release(); 

    EXPECT_EQ(Graph::capacity(), 8);
    EXPECT_EQ(Graph::available(), 8);
} 

*/