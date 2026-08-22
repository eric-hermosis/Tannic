#include <gtest/gtest.h>
#include <tannic/c/allocations.h>
#include <tannic/environments.hpp>
#include <tannic/memory.hpp> 

namespace tannic {

TEST(TestMemory, TestReferences) {
    Memory* memory = new Memory(); 
    memory->bump();
    memory->bump(); 
    EXPECT_FALSE(memory->dump());
    EXPECT_TRUE(memory->dump()); 
    delete memory;
}
 
TEST(TestMemory, TestBody) {
    auto memory = new Memory();

    EXPECT_EQ(memory->body(), nullptr);

    memory->acquire();

    ASSERT_NE(memory->body(), nullptr);

    memory->set(sizeof(int), Host()); 
    auto body = memory->body();

    ASSERT_NE(body, nullptr);
    EXPECT_EQ(body->domain, HOST);
    EXPECT_STREQ(body->allocator.name, "malloc");
    EXPECT_EQ(body->buffer.size, sizeof(int));
    EXPECT_EQ(body->buffer.address, nullptr);

    memory->allocate(); 
    ASSERT_NE(body->buffer.address, nullptr);

    memory->deallocate();
    EXPECT_EQ(body->buffer.address, nullptr);

    memory->release();
    EXPECT_EQ(memory->body(), nullptr);  
    delete memory;
}

TEST(TestMemory, TestReuse) {
    auto memory = new Memory();

    memory->acquire();
    auto* first = memory->body();

    ASSERT_NE(first, nullptr);

    memory->release();

    EXPECT_EQ(memory->body(), nullptr);

    memory->acquire();
    auto* second = memory->body();

    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second, first);

    memory->set(sizeof(int), Host()); 
    ASSERT_NE(memory->body(), nullptr); 
    memory->reset(); 
    memory->release();
    delete memory;
}

}