#include <algo/arithmetic.h>
#include <arithmetic/long_integer.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

TEST(LongIntegerTest, EqualTest) {
  constexpr int64_t kVal = 1223;
  arithmetic::LongInteger val2 = kVal;
  arithmetic::LongInteger val3 = kVal;
  EXPECT_TRUE(val2 == val3);
  EXPECT_TRUE(val2 == val2);
}

TEST(LongIntegerTest, LessTest) {
  constexpr auto kVal1 = 123;
  constexpr auto kVal2 = 1223;
  arithmetic::LongInteger val1 = kVal1;
  arithmetic::LongInteger val2 = kVal2;
  EXPECT_TRUE(val1 < val2);
}

TEST(LongIntegerTest, GreaterTest) {
  constexpr auto kVal1 = -123;
  constexpr auto kVal2 = 1223;
  constexpr auto kVal3 = 123;
  arithmetic::LongInteger val1 = kVal1;
  arithmetic::LongInteger val2 = kVal2;
  arithmetic::LongInteger val3 = kVal3;
  EXPECT_TRUE(val2 > val1);
  EXPECT_TRUE(val2 > val3);
}

TEST(LongIntegerTest, PrintTest) {
  constexpr auto kVal1 = 23423;
  arithmetic::LongInteger val = kVal1;
  std::ostringstream k_out;
  std::ostringstream out;
  k_out << kVal1;
  out << val;
  EXPECT_EQ(k_out.str(), out.str());
  k_out.str("");
  out.str("");
  constexpr auto kVal2 = 123124676898977887;
  val = kVal2;
  k_out << kVal2;
  out << val;
  EXPECT_EQ(k_out.str(), out.str());
}

TEST(LongIntegerTest, UnsignedAdditionTest) {
  constexpr auto kVal1 = 23423;
  constexpr auto kVal2 = 93783655;
  arithmetic::LongInteger val = kVal1;
  val += kVal2;
  std::ostringstream k_out;
  std::ostringstream out;
  k_out << kVal1 + kVal2;
  out << val;
  EXPECT_EQ(k_out.str(), out.str());
  out.str("");
  val = 0;
  constexpr auto kVal3 = 1231246768989778;
  constexpr auto kTimes = 1000;
  for (unsigned i = 0; i < kTimes; ++i) { val += kVal3; }
  out << val;
  EXPECT_EQ(out.str(), "1231246768989778000");
}

TEST(LongIntegerTest, SignedAdditionTest) {
  constexpr auto kVal1 = 23423;
  constexpr auto kVal2 = -93783655;
  arithmetic::LongInteger val = kVal1;
  val += kVal2;
  std::ostringstream k_out;
  std::ostringstream out;
  k_out << kVal1 + kVal2;
  out << val;
  EXPECT_EQ(out.str(), k_out.str());
  out.str("");
  val = 0;
  constexpr auto kVal3 = -12312467689;
  constexpr auto kTimes = 1000;
  for (unsigned i = 0; i < kTimes; ++i) { val += kVal3; }
  out << val;
  EXPECT_EQ(out.str(), "-12312467689000");
  k_out.str("");
  out.str("");
  constexpr auto kVal4 = 234324324;
  constexpr auto kVal5 = -123124676898977;
  val = kVal4;
  val += kVal5;
  k_out << kVal4 + kVal5;
  out << val;
  EXPECT_EQ(k_out.str(), out.str());
}

TEST(LongIntegerTest, SubstractionTest) {
  constexpr auto kVal1 = 23123123233423;
  constexpr auto kVal2 = -937831233223655;
  arithmetic::LongInteger val = kVal1;
  val -= kVal2;
  std::ostringstream k_out;
  std::ostringstream out;
  k_out << kVal1 - kVal2;
  out << val;
  EXPECT_EQ(k_out.str(), out.str());
  k_out.str("");
  out.str("");
  constexpr auto kVal3 = -937831233223655;
  constexpr auto kVal4 = 23123123233423;
  val = kVal3;
  val -= kVal4;
  k_out << kVal3 - kVal4;
  out << val;
  EXPECT_EQ(k_out.str(), out.str());
}

TEST(LongIntegerTest, PowTest) {
  constexpr auto kVal1 = 1234235435;
  constexpr auto kPow1 = 2;
  arithmetic::LongInteger val{ kVal1 };
  std::ostringstream out;
  val = algo::arithmetic::FastPow(val, kPow1);
  std::string answer1 = "1523337109009639225";
  out << val;
  EXPECT_EQ(out.str(), answer1);
}