#include <arithmetic/long_integer.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

TEST(LongIntegerTest, EqualTest) {
  arithmetic::LongInteger val2 = 1223;
  arithmetic::LongInteger val3 = 1223;
  EXPECT_TRUE(val2 == val3);
  EXPECT_TRUE(val2 == val2);
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

TEST(LongIntegerTest, PrintTest) {
  auto val = 23423ull;
  arithmetic::LongInteger long_val = val;
  std::ostringstream out;
  std::ostringstream long_out;
  out << val;
  long_out << long_val;
  EXPECT_EQ(out.str(), long_out.str());
  out.str("");
  long_out.str("");
  val = 123124676898977887ull;
  long_val = val;
  out << val;
  long_out << long_val;
  EXPECT_EQ(out.str(), long_out.str());
}

TEST(LongIntegerTest, UnsignedAdditionTest) {
  auto val1 = 23423, val2 = 93783655;
  arithmetic::LongInteger long_val = val1;
  long_val += val2;
  std::ostringstream out;
  std::ostringstream long_out;
  out << val1 + val2;
  long_out << long_val;
  EXPECT_EQ(out.str(), long_out.str());
  long_out.str("");
  auto val = 1231246768989778ull;
  long_val = 0;
  for (unsigned i = 0; i < 1000; ++i) {
    long_val += val;
  }
  long_out << long_val;
  EXPECT_EQ(long_out.str(), "1231246768989778000");
}

TEST(LongIntegerTest, SignedAdditionTest) {
  auto val1 = 23423, val2 = -93783655;
  arithmetic::LongInteger long_val = val1;
  long_val += val2;
  std::ostringstream out;
  std::ostringstream long_out;
  out << val1 + val2;
  long_out << long_val;
  EXPECT_EQ(out.str(), long_out.str());
  long_out.str("");
  auto val = -12312467689;
  long_val = 0;
  for (unsigned i = 0; i < 1000; ++i) {
    val = val;
    long_val += val;
  }
  long_out << long_val;
  EXPECT_EQ(long_out.str(), "-12312467689000");
  long_out.str("");
  out.str("");
  auto val3 = 234324324ll;
  auto val4 = -123124676898977ll;
  long_val = val3;
  long_val += val4;
  out << val3 + val4;
  long_out << long_val;
  EXPECT_EQ(long_out.str(), out.str());
}

TEST(LongIntegerTest, SubstractionTest) {
  auto val1 = 23123123233423, val2 = -937831233223655;
  arithmetic::LongInteger long_val = val1;
  long_val -= val2;
  std::ostringstream out;
  std::ostringstream long_out;
  out << val1 - val2;
  long_out << long_val;
  EXPECT_EQ(out.str(), long_out.str());
  long_out.str("");
  out.str("");
  val1 = -937831233223655;
  val2 = 23123123233423;
  long_val = val1;
  long_val -= val2;
  out << val1 - val2;
  long_out << long_val;
  EXPECT_EQ(out.str(), long_out.str());
}
