#include <gtest/gtest.h>
#include <tannic/tensors.hpp>
#include <tannic/operations.hpp>

/*
#include <tannic/graph.hpp>

using namespace tannic;

TEST(TestTensors, TestGraphLifetime) { 
    {
        Tensor x; x.initialize();
        Tensor y; y.initialize();
        Tensor z; z.initialize();
        Tensor w = x*y + y*z + z*x;

        EXPECT_EQ(Graph::capacity(), 8);
        EXPECT_EQ(Graph::available(), 0);
    }
 
    EXPECT_EQ(Graph::capacity(), 8);
    EXPECT_EQ(Graph::available(), 8);

    {
        Tensor x; x.initialize();
        Tensor y = x;
        EXPECT_EQ(Graph::capacity(), 8);
        EXPECT_EQ(Graph::available(), 7);
    }
    
    EXPECT_EQ(Graph::capacity(), 8);
    EXPECT_EQ(Graph::available(), 8);
}

*/