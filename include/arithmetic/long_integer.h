#ifndef ALGORITHMS_INCLUDE_ARITHMETIC_LONG_INTEGER_H_
#define ALGORITHMS_INCLUDE_ARITHMETIC_LONG_INTEGER_H_

#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

#include "algo/arithmetic.h"

namespace arithmetic {

class LongInteger final {
 public:
  LongInteger(int64_t number = 0);

  LongInteger &operator+=(const LongInteger &rhs);

  LongInteger &operator-=(const LongInteger &rhs);

  LongInteger &operator*=(const LongInteger &rhs);

  void Abs() noexcept;

  void Print(std::ostream &out) const;

  bool Equal(const LongInteger &rhs) const;

  bool Less(const LongInteger &rhs) const;

 private:
  void AddAsAbsoluteValues(const LongInteger &rhs);

  void SubAsAbsoluteValues(const LongInteger &rhs);

  void ToComplement();

  std::vector<uint64_t> numbers_;
  bool signed_;
  constexpr static uint32_t kNDigitsInNumber =
      std::numeric_limits<uint64_t>::digits10 / 2 - 1;
  constexpr static uint64_t kModule =
      algo::arithmetic::FastPow<uint64_t>(10, kNDigitsInNumber);
};

LongInteger operator+(const LongInteger &lhs, const LongInteger &rhs);

LongInteger operator-(const LongInteger &lhs, const LongInteger &rhs);

bool operator<(const LongInteger &lhs, const LongInteger &rhs);

bool operator<=(const LongInteger &lhs, const LongInteger &rhs);

bool operator>(const LongInteger &lhs, const LongInteger &rhs);

bool operator>=(const LongInteger &lhs, const LongInteger &rhs);

bool operator==(const LongInteger &lhs, const LongInteger &rhs);

bool operator!=(const LongInteger &lhs, const LongInteger &rhs);

std::ostream &operator<<(std::ostream &out, const LongInteger &val);

}  // namespace arithmetic

template<>
struct algo::arithmetic::ArithmeticTraits<arithmetic::LongInteger, true> {
  static ::arithmetic::LongInteger identity() { return 1; }
  static void multiply(::arithmetic::LongInteger &val1,
                       const ::arithmetic::LongInteger &val2) {
    val1 *= val2;
  }
};

#endif  // ALGORITHMS_INCLUDE_ARITHMETIC_LONG_INTEGER_H_
