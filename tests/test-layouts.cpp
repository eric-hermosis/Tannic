#include <gtest/gtest.h>
#include <tannic/layouts.hpp>

using namespace tannic;

TEST(TestLayouts, ShapeConstexprConstruction) {
    constexpr Shape s{1, 2, 3};
    static_assert(s.size() == 3);
    static_assert(s[0] == 1);
    static_assert(s[1] == 2);
    static_assert(s[2] == 3);
    static_assert(s[-1] == 3);
    static_assert(s[-2] == 2);
    static_assert(s[-3] == 1);
}

TEST(TestLayouts, ShapeConstexprEquality) {
    constexpr Shape a{1, 2, 3};
    constexpr Shape b{1, 2, 3};
    constexpr Shape c{1, 2, 4};

    static_assert(a == b);
    static_assert(!(a == c));
}

TEST(TestLayouts, ShapeIterableConstructor) {
    std::vector<int> v = {2, 4, 6};

    Shape s(v);

    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s[0], 2);
    EXPECT_EQ(s[1], 4);
    EXPECT_EQ(s[2], 6);
}

TEST(TestLayouts, ShapeIteratorConstructor) {
    std::array<int, 3> arr = {7, 8, 9};

    Shape s(arr.begin(), arr.end());

    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s[0], 7);
    EXPECT_EQ(s[1], 8);
    EXPECT_EQ(s[2], 9);
}

TEST(TestLayouts, ShapeNegativeIndexing) {
    Shape s(10, 20, 30);

    EXPECT_EQ(s[-1], 30);
    EXPECT_EQ(s[-2], 20);
    EXPECT_EQ(s[-3], 10);
}

TEST(TestLayouts, ShapeAppend) {
    Shape s(1, 2);

    s.append(3);
    s.append(4);

    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s[2], 3);
    EXPECT_EQ(s[3], 4);
}

TEST(TestLayouts, ShapeResize) {
    Shape s(1, 2, 3, 4);

    s.resize(2);

    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s[0], 1);
    EXPECT_EQ(s[1], 2);
}
 
TEST(TestLayouts, ShapeFrontBack) {
    Shape s(5, 6, 7);

    EXPECT_EQ(s.front(), 5);
    EXPECT_EQ(s.back(), 7);
}

TEST(TestLayouts, ShapeEquality) {
    Shape a(1, 2, 3);
    Shape b(1, 2, 3);
    Shape c(3, 2, 1);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
} 

TEST(TestLayouts, ShapeAppendExceedsLimitThrows) {
    Shape s(1,2,3,4,5,6,7,8);

    EXPECT_THROW(s.append(9), Exception);
}

TEST(TestLayouts, ShapeInvalidNegativeDimensionThrows) {
    EXPECT_THROW(
        Shape(1, -5, 3),
        Exception
    );
}

TEST(TestLayouts, ShapeAppendInvalidDimensionThrows) {
    Shape s(1, 2, 3);

    EXPECT_THROW(s.append(-5), Exception);
}


TEST(TestLayouts, ShapeDynamicDimensionAllowed) {
    Shape s(1, -1, 3);

    EXPECT_EQ(s[1], -1);
}

TEST(TestLayouts, ShapeAddressAccess) {
    Shape s(3, 4, 5);

    auto ptr = s.address();

    EXPECT_EQ(ptr[0], 3);
    EXPECT_EQ(ptr[1], 4);
    EXPECT_EQ(ptr[2], 5);
}
 

TEST(TestLayouts, ShapeIteration) {
    Shape s(1, 2, 3);

    int expected = 1;
    for (auto v : s) {
        EXPECT_EQ(v, expected++);
    }
}


TEST(TestLayouts, StridesConstexprConstruction) {
    constexpr Strides s{1, 2, 3};
    static_assert(s.size() == 3);
    static_assert(s[0] == 1);
    static_assert(s[1] == 2);
    static_assert(s[2] == 3);
    static_assert(s[-1] == 3);
    static_assert(s[-2] == 2);
    static_assert(s[-3] == 1);
}

TEST(TestLayouts, StridesConstexprEquality) {
    constexpr Strides a{1, 2, 3};
    constexpr Strides b{1, 2, 3};
    constexpr Strides c{1, 2, 4};

    static_assert(a == b);
    static_assert(!(a == c));
}

TEST(TestLayouts, StridesConstexprInitializerList) {
    constexpr Strides s{4, 5, 6};

    static_assert(s.size() == 3);
    static_assert(s[0] == 4);
    static_assert(s[1] == 5);
    static_assert(s[2] == 6);
}

TEST(TestLayouts, StridesIteratorConstructor) {
    std::array<int, 3> arr = {7, 8, 9};

    Strides s(arr.begin(), arr.end());

    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s[0], 7);
    EXPECT_EQ(s[1], 8);
    EXPECT_EQ(s[2], 9);
}

TEST(TestLayouts, StridesNegativeIndexing) {
    Strides s(10, 20, 30);

    EXPECT_EQ(s[-1], 30);
    EXPECT_EQ(s[-2], 20);
    EXPECT_EQ(s[-3], 10);
}

TEST(TestLayouts, StridesAppend) {
    Strides s(1, 2);

    s.append(3);
    s.append(4);

    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s[2], 3);
    EXPECT_EQ(s[3], 4);
}

TEST(TestLayouts, StridesResize) {
    Strides s(1, 2, 3, 4);

    s.resize(2);

    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s[0], 1);
    EXPECT_EQ(s[1], 2);
}

TEST(TestLayouts, StridesFrontBack) {
    Strides s(5, 6, 7);

    EXPECT_EQ(s.front(), 5);
    EXPECT_EQ(s.back(), 7);
}

TEST(TestLayouts, StridesEquality) {
    Strides a(1, 2, 3);
    Strides b(1, 2, 3);
    Strides c(3, 2, 1);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(TestLayouts, StridesAppendExceedsLimitThrows) {
    Strides s(1,2,3,4,5,6,7,8);

    EXPECT_THROW(s.append(9), Exception);
}

TEST(TestLayouts, StridesInvalidNegativeDimensionThrows) {
    EXPECT_THROW(
        Strides(1, -5, 3),
        Exception
    );
}

TEST(TestLayouts, StridesAppendInvalidDimensionThrows) {
    Strides s(1, 2, 3);

    EXPECT_THROW(s.append(-5), Exception);
}

TEST(TestLayouts, StridesDynamicDimensionAllowed) {
    Strides s(1, -1, 3);

    EXPECT_EQ(s[1], -1);
}

TEST(TestLayouts, StridesAddressAccess) {
    Strides s(3, 4, 5);

    auto ptr = s.address();

    EXPECT_EQ(ptr[0], 3);
    EXPECT_EQ(ptr[1], 4);
    EXPECT_EQ(ptr[2], 5);
}

TEST(TestLayouts, StridesIteration) {
    Strides s(1, 2, 3);

    int expected = 1;
    for (auto v : s) {
        EXPECT_EQ(v, expected++);
    }
}