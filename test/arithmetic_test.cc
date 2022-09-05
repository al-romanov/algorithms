#include <algo/arithmetic.h>
#include <gtest/gtest.h>

TEST(PowTest, Pow0Test) {
    unsigned val = 6;
    val = algo::arithmetic::FastPow(val, 0);
    EXPECT_EQ(val, 1);
}

TEST(PowTest, Val1Test) {
    unsigned val = 1;
    val = algo::arithmetic::FastPow(val, 23);
    EXPECT_EQ(val, 1);
}

TEST(PowTest, Val0Test) {
    unsigned val = 0;
    val = algo::arithmetic::FastPow(val, 23);
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
    val = algo::arithmetic::FastPow(val, 4);
    EXPECT_DOUBLE_EQ(val, 1296);
}

TEST(PowTest, SignedTest) {
    unsigned val = -6;
    val = algo::arithmetic::FastPow(val, 2);
    EXPECT_EQ(val, 36);
}

namespace details {

struct MyStruct {
    int val;

    MyStruct(int arg) : val(arg) {}

    MyStruct &operator*=(const MyStruct &rhs) {
        val *= rhs.val;
        return *this;
    }
};

bool operator==(const MyStruct &lhs, const MyStruct &rhs) {
    return lhs.val == rhs.val;
}

}  // namespace details

template <>
struct algo::arithmetic::ArithmeticTraits<details::MyStruct> {
    static details::MyStruct identity() {
        return details::MyStruct{1};
    }
};

TEST(PowTest, CustomArithmeticConstantsTest) {
    details::MyStruct val{2};
    val = algo::arithmetic::FastPow(val, 5);   
    const details::MyStruct correct_res{32};
    EXPECT_EQ(val, correct_res);
}
