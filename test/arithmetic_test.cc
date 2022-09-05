#include <algo/arithmetic.h>
#include <gtest/gtest.h>

TEST(PowTest, Pow0Test) {
    unsigned val = 6;
    unsigned pow = 0;
    val = algo::arithmetic::FastPow(val, pow);
    EXPECT_EQ(val, 1);
}

TEST(PowTest, Val1Test) {
    unsigned val = 1;
    unsigned pow = 23;
    val = algo::arithmetic::FastPow(val, pow);
    EXPECT_EQ(val, 1);
}

TEST(PowTest, Val0Test) {
    unsigned val = 0;
    unsigned pow = 23;
    val = algo::arithmetic::FastPow(val, pow);
    EXPECT_EQ(val, 0);
}

TEST(PowTest, UnsignedPow) {
    unsigned val = 6;
    unsigned pow = 4;
    val = algo::arithmetic::FastPow(val, pow);
    EXPECT_EQ(val, 1296);
}

TEST(PowTest, DoublePow) {
    double val = 6;
    unsigned pow = 4;
    val = algo::arithmetic::FastPow(val, pow);
    EXPECT_DOUBLE_EQ(val, 1296);
}

TEST(PowTest, SignedTest) {
    unsigned val = -6;
    unsigned pow = 2;
    val = algo::arithmetic::FastPow(val, pow);
    EXPECT_EQ(val, 36);
}
