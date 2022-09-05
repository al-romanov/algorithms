#include <algo/arithmetic.h>
#include <gtest/gtest.h>

TEST(LongIntegerTest, EqualTest) {
    arithmetic::LongInteger val2 = 1223;
    arithmetic::LongInteger val3 = 1223;
    EXPECT_TRUE(val2 == val3);
    EXPECT_TRUE(val2 == val2);
    EXPECT_TRUE(val2 == val3);
}

TEST(LongIntegerTest, LessTest) {
    arithmetic::LongInteger val1 = 123;
    arithmetic::LongInteger val2 = 1223;
    EXPECT_TRUE(val1 < val2);
}

TEST(LongIntegerTest, GreaterTest) {
    arithmetic::LongInteger val1 = -123;
    arithmetic::LongInteger val2 = 1223u;
    arithmetic::LongInteger val3 = 123;
    EXPECT_TRUE(val2 > val1);
    EXPECT_TRUE(val2 > val3);
}
