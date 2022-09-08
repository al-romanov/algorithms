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

  explicit LongInteger(uint64_t number);

  LongInteger &operator+=(const LongInteger &rhs);

  LongInteger &operator-=(const LongInteger &rhs);

  void Abs() noexcept;

  void Print(std::ostream &out) const;

  bool Equal(const LongInteger &rhs) const;

  bool Less(const LongInteger &rhs) const;

 private:
  void AddAsAbsoluteValues_(const LongInteger &rhs);

  void SubAsAbsoluteValues_(const LongInteger &rhs);

  void ToComplement_();

 private:
  std::vector<uint64_t> numbers_;
  bool signed_;
  constexpr static uint32_t n_digits_in_number_ =
      std::numeric_limits<uint64_t>::digits10 / 2 - 1;
  constexpr static uint64_t module_ =
      algo::arithmetic::FastPow(10ull, n_digits_in_number_);
};

LongInteger operator+(const LongInteger &lhs, const LongInteger &rhs);

bool operator<(const LongInteger &lhs, const LongInteger &rhs);

bool operator<=(const LongInteger &lhs, const LongInteger &rhs);

bool operator>(const LongInteger &lhs, const LongInteger &rhs);

bool operator>=(const LongInteger &lhs, const LongInteger &rhs);

bool operator==(const LongInteger &lhs, const LongInteger &rhs);

bool operator!=(const LongInteger &lhs, const LongInteger &rhs);

std::ostream &operator<<(std::ostream &out, const LongInteger &val);

}  // namespace arithmetic

#endif  // ALGORITHMS_INCLUDE_ARITHMETIC_LONG_INTEGER_H_
