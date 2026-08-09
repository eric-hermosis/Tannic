#include <gtest/gtest.h>
#include <tannic/symbols.hpp>
#include <tannic/types.hpp>
#include <tannic/layouts.hpp>

/*
#include <tannic/graph/nodes.hpp>

using namespace tannic;

TEST(TestGraph, TestNodes) {
    struct Example{};
    auto symbol = Example{};
    auto type = float32;
    auto layout = Layout(Shape{2,2});

    Node* x = Node::create(symbol, type, layout);
    Node* y = Node::create(symbol, type, layout);
    Node* z = Node::create(symbol, type, layout);

    Node* xy =  Node::create(symbol, type, layout); xy->link(x); xy->link(y);
    Node* yz =  Node::create(symbol, type, layout); yz->link(y); yz->link(z);
    Node* zx =  Node::create(symbol, type, layout); zx->link(z); zx->link(x);

    Node* xyyz =  Node::create(symbol, type, layout); xyyz->link(xy); xyyz->link(yz);
    Node* xyyzzx =  Node::create(symbol, type, layout); xyyzzx->link(xyyz); xyyzzx->link(zx);
 
    xyyzzx->acquire();
    xyyzzx->release(); 
}

*/