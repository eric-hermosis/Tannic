#include <gtest/gtest.h> 
#include <tannic/types.hpp> 

using namespace tannic;

TEST(TestTypes, SizeofValues) {
    static_assert(Type(boolean).size()    == sizeof(int8_t));
    static_assert(Type(uint8).size()      == sizeof(uint8_t));
    static_assert(Type(uint16).size()     == sizeof(uint16_t));
    static_assert(Type(uint32).size()     == sizeof(uint32_t));
    static_assert(Type(uint64).size()     == sizeof(uint64_t));

    static_assert(Type(int8).size()       == sizeof(int8_t));
    static_assert(Type(int16).size()      == sizeof(int16_t));
    static_assert(Type(int32).size()      == sizeof(int32_t));
    static_assert(Type(int64).size()      == sizeof(int64_t));

    static_assert(Type(float16).size()    == sizeof(float) / 2);
    static_assert(Type(bfloat16).size()   == sizeof(float) / 2);
    static_assert(Type(float32).size()    == sizeof(float));
    static_assert(Type(float64).size()    == sizeof(double));

    static_assert(Type(complex64).size()  == 2 * sizeof(float));
    static_assert(Type(complex128).size() == 2 * sizeof(double));

    static_assert(Type(any).size()        == 0);
    static_assert(Type(unknown).size()    == 0);
}

TEST(TestTypes, NameofValues) {
    static_assert(std::string(Type(boolean).name())    == "boolean");

    static_assert(std::string(Type(uint8).name())      == "uint8");
    static_assert(std::string(Type(uint16).name())     == "uint16");
    static_assert(std::string(Type(uint32).name())     == "uint32");
    static_assert(std::string(Type(uint64).name())     == "uint64");

    static_assert(std::string(Type(int8).name())       == "int8");
    static_assert(std::string(Type(int16).name())      == "int16");
    static_assert(std::string(Type(int32).name())      == "int32");
    static_assert(std::string(Type(int64).name())      == "int64");

    static_assert(std::string(Type(float16).name())    == "float16");
    static_assert(std::string(Type(bfloat16).name())   == "bfloat16");
    static_assert(std::string(Type(float32).name())    == "float32");
    static_assert(std::string(Type(float64).name())    == "float64");

    static_assert(std::string(Type(complex64).name())  == "complex64");
    static_assert(std::string(Type(complex128).name()) == "complex128");

    static_assert(std::string(Type(any).name())        == "any"); 
}

TEST(TestTypes, OstreamOperator) {
    {
        std::ostringstream oss;
        oss << Type(float64);
        EXPECT_EQ(oss.str(), "float64");
    }
    {
        std::ostringstream oss;
        oss << Type(uint32);
        EXPECT_EQ(oss.str(), "uint32");
    }
    {
        std::ostringstream oss;
        oss << Type(any);
        EXPECT_EQ(oss.str(), "any");
    } 
}
