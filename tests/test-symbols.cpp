#include <gtest/gtest.h>
#include <tannic/symbols.hpp>

using namespace tannic;
 
TEST(TestSymbols, TestReflection) {
    class ExampleSymbol {};
    auto symbol = Symbol(ExampleSymbol{});
    EXPECT_EQ(symbol.name(), "ExampleSymbol");
}