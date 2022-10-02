#include "arithmetic/long_integer.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <iterator>

namespace arithmetic {

LongInteger::LongInteger(int64_t number) : signed_(number < 0) {
  number = std::abs(number);
  numbers_.push_back(number % kModule);
  number /= kModule;
  while (number != 0) {
    numbers_.push_back(number % kModule);
    number /= kModule;
  }
}

LongInteger &LongInteger::operator+=(const LongInteger &rhs) {
  if (signed_ != rhs.signed_) {
    bool prev_signed = signed_;
    SubAsAbsoluteValues(rhs);
    signed_ = prev_signed != signed_;
  } else {
    AddAsAbsoluteValues(rhs);
  }
  return *this;
}

LongInteger &LongInteger::operator-=(const LongInteger &rhs) {
  if (signed_ != rhs.signed_) {
    AddAsAbsoluteValues(rhs);
  } else {
    bool prev_signed = signed_;
    SubAsAbsoluteValues(rhs);
    signed_ = prev_signed != signed_;
  }
  return *this;
}

LongInteger &LongInteger::operator*=(const LongInteger &rhs) {
  LongInteger res;
  res.numbers_.resize(numbers_.size() + rhs.numbers_.size());
  auto res_it = res.numbers_.begin();
  for (auto val1 : rhs.numbers_) {
    auto out_it = res_it;
    uint64_t remainder = 0;
    for (auto val2 : numbers_) {
      auto res = *out_it + val1 * val2 + remainder;
      remainder = res / kModule;
      *out_it = res % kModule;
      std::cout << *out_it << std::endl;
      ++out_it;
    }
    *out_it += remainder;
    ++res_it;
  }
  std::swap(res, *this);
  while (numbers_.back() == 0 && numbers_.size() > 1) { numbers_.pop_back(); }
  return *this;
}

void LongInteger::AddAsAbsoluteValues(const LongInteger &rhs) {
  auto max_size = std::max(numbers_.size(), rhs.numbers_.size());
  numbers_.resize(max_size + 1);
  uint64_t remainder = 0;
  auto it = numbers_.begin();
  for (auto val : rhs.numbers_) {
    *it += val + remainder;
    remainder = *it / kModule;
    *it %= kModule;
    ++it;
  }
  std::transform(it, numbers_.end(), it, [&remainder](auto val) {
    auto res = val + remainder;
    remainder = res / kModule;
    return res % kModule;
  });
  if (numbers_.back() == 0) { numbers_.pop_back(); }
}

void LongInteger::SubAsAbsoluteValues(const LongInteger &rhs) {
  auto max_size = std::max(numbers_.size(), rhs.numbers_.size());
  numbers_.resize(max_size);
  signed_ = false;
  uint64_t remainder = 0;
  auto it = numbers_.begin();
  for (auto val : rhs.numbers_) {
    auto current_remainder = remainder;
    remainder = *it < val + remainder ? 1 : 0;
    *it = (*it + kModule - val - current_remainder) % kModule;
    ++it;
  }
  if (remainder != 0) {
    ToComplement();
    signed_ = true;
  }
  while (numbers_.back() == 0 && numbers_.size() > 1) { numbers_.pop_back(); }
}

void LongInteger::ToComplement() {
  auto it = numbers_.begin();
  *it = (kModule - *it) % kModule;
  ++it;
  std::transform(it, numbers_.end(), it,
                 [](auto val) { return kModule - val - 1; });
}

void LongInteger::Abs() noexcept { signed_ = false; }

void LongInteger::Print(std::ostream &out) const {
  if (signed_) { out << "-"; }
  auto it = numbers_.rbegin();
  out << *it;
  ++it;
  for (; it != numbers_.rend(); ++it) {
    out << std::setfill('0') << std::setw(kNDigitsInNumber) << *it;
  }
}

bool LongInteger::Equal(const LongInteger &rhs) const {
  if (signed_ != rhs.signed_) { return false; }
  return numbers_ == rhs.numbers_;
}

bool LongInteger::Less(const LongInteger &rhs) const {
  if (signed_ && !rhs.signed_) { return true; }
  if (!signed_ && rhs.signed_) { return false; }
  auto first = numbers_.rbegin();
  auto last = numbers_.rend();
  auto rhs_first = rhs.numbers_.rbegin();
  auto rhs_last = rhs.numbers_.rend();
  if (signed_) {
    return std::lexicographical_compare(rhs_first, rhs_last, first, last);
  }
  return std::lexicographical_compare(first, last, rhs_first, rhs_last);
}

LongInteger operator+(const LongInteger &lhs, const LongInteger &rhs) {
  LongInteger res{ lhs };
  res += rhs;
  return res;
}

LongInteger operator-(const LongInteger &lhs, const LongInteger &rhs) {
  LongInteger res{ lhs };
  res -= rhs;
  return res;
}

bool operator<(const LongInteger &lhs, const LongInteger &rhs) {
  return lhs.Less(rhs);
}

bool operator<=(const LongInteger &lhs, const LongInteger &rhs) {
  return !rhs.Less(lhs);
}

bool operator>(const LongInteger &lhs, const LongInteger &rhs) {
  return rhs.Less(lhs);
}

bool operator>=(const LongInteger &lhs, const LongInteger &rhs) {
  return !lhs.Less(rhs);
}

bool operator==(const LongInteger &lhs, const LongInteger &rhs) {
  return lhs.Equal(rhs);
}

bool operator!=(const LongInteger &lhs, const LongInteger &rhs) {
  return !lhs.Equal(rhs);
}

std::ostream &operator<<(std::ostream &out, const LongInteger &val) {
  val.Print(out);
  return out;
}

}  // namespace arithmetic
