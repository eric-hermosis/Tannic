#include <gtest/gtest.h>
#include <tannic/visitors.hpp>

using namespace tannic;

TEST(TestVisitor, TestVisitor) {
    Visitor visitor;
    visitor.set(10);
    EXPECT_EQ(visitor.visited(10), false);
    visitor.visit(10);

    EXPECT_EQ(visitor.visited(10), true);
    EXPECT_EQ(visitor.visited(9), false);

    visitor.reset();
    EXPECT_EQ(visitor.visited(10), false);
    visitor.visit(10);

    EXPECT_EQ(visitor.visited(10), true);
    EXPECT_EQ(visitor.visited(9), false);
}