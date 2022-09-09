#include <algo/arithmetic.h>
#include <gtest/gtest.h>

TEST(PowTest, Pow0Test) {
  EXPECT_EQ(algo::arithmetic::FastPow(6, 0), 1);
}

TEST(PowTest, Val1Test) {
  EXPECT_EQ(algo::arithmetic::FastPow(1, 23), 1);
}

TEST(PowTest, Val0Test) {
  EXPECT_EQ(algo::arithmetic::FastPow(0, 23), 0);
}

TEST(PowTest, UnsignedPow) {
  EXPECT_EQ(algo::arithmetic::FastPow(6U, 4), 1296);
}

TEST(PowTest, DoublePow) {
  EXPECT_DOUBLE_EQ(algo::arithmetic::FastPow(6.0, 4), 1296);
}

TEST(PowTest, SignedTest) {
  constexpr int kVal = -6;
  EXPECT_EQ(algo::arithmetic::FastPow(kVal, 2), 36);
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
  static details::MyStruct identity() { return details::MyStruct{1}; }
};

TEST(PowTest, CustomArithmeticConstantsTest) {
  const details::MyStruct val{2};
  const details::MyStruct correct_res{32};
  EXPECT_EQ(algo::arithmetic::FastPow(val, 5), correct_res);
}
