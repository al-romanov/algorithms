#ifndef ALGORITHMS_INCLUDE_ARITHMETIC_LONG_INTEGER_H_
#define ALGORITHMS_INCLUDE_ARITHMETIC_LONG_INTEGER_H_

#include <iostream>
#include <limits>
#include <vector>

#include <algo/arithmetic.h>

namespace arithmetic {

class LongInteger final {
public:
    LongInteger(long long number = 0);
    
    explicit LongInteger(unsigned long long number);

    LongInteger &operator+=(const LongInteger &rhs);

    void Abs() noexcept;

    void Print(std::ostream &out) const;

    bool Equal(const LongInteger &rhs) const;

    bool Less(const LongInteger &rhs) const;

private:
    void AddAsAbsoluteValues_(const LongInteger &rhs);

    void SubAsAbsoluteValues_(const LongInteger &rhs);

private:
    std::vector<unsigned long long> numbers_;
    bool signed_;
    constexpr static unsigned n_digits_in_number_ = std::numeric_limits<unsigned long long>::digits10 / 2 - 1;
    constexpr static unsigned module_ = algo::arithmetic::FastPow(10u, n_digits_in_number_);
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
