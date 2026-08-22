#include <gtest/gtest.h>
#include <tannic/types.hpp>
#include <tannic/layouts.hpp>
#include <tannic/symbols.hpp>
#include <tannic/graphs.hpp>
#include <tannic/c/graphs.h>

using namespace tannic;

TEST(TestNodes, TestReferences) {
    auto node = new Node(); 
    node->bump();
    node->bump(); 
    EXPECT_FALSE(node->dump());
    EXPECT_TRUE(node->dump()); 
    delete node;
}

TEST(TestNodes, TestBody) {
    auto node = new Node();

    EXPECT_EQ(node->body(), nullptr);

    node->acquire();

    ASSERT_NE(node->body(), nullptr);

    node->set(Node{}, Type{float32}, Shape{2, 2});

    auto body = node->body();

    ASSERT_NE(body, nullptr);
    EXPECT_EQ(body->type, float32);
    EXPECT_EQ(body->layout.rank, 2);

    EXPECT_EQ(body->layout.shape.sizes[0], 2);
    EXPECT_EQ(body->layout.shape.sizes[1], 2);


    node->reset();  
    node->release();

    EXPECT_EQ(node->body(), nullptr);

    delete node;
} 

TEST(TestNodes, TestReuse) {
    auto node = new Node();

    node->acquire();
    auto* first = node->body();

    ASSERT_NE(first, nullptr);

    node->release();

    EXPECT_EQ(node->body(), nullptr);

    node->acquire();
    auto* second = node->body();

    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second, first);

    node->set(Node{}, Type{float32}, Shape{2, 2});

    ASSERT_NE(node->body(), nullptr);
    EXPECT_STREQ(node->body()->name, "Node");
    EXPECT_EQ(node->body()->type, float32);
    EXPECT_EQ(node->body()->layout.rank, 2); 
    node->reset(); 
    node->release();
    delete node;
}