#include "arithmetic/long_integer.h"

#include <algorithm>
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

LongInteger::LongInteger(uint64_t number) : signed_(false) {
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

void LongInteger::AddAsAbsoluteValues(const LongInteger &rhs) {
  auto max_size = std::max(numbers_.size(), rhs.numbers_.size());
  numbers_.resize(max_size + 1);
  auto remainder = 0ULL;
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
  auto remainder = 0ULL;
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
  if (signed_) { return numbers_ > rhs.numbers_; }
  return numbers_ < rhs.numbers_;
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
