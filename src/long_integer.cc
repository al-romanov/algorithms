#include "arithmetic/long_integer.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>

namespace arithmetic {

LongInteger::LongInteger(long long number) :
    signed_(number < 0) {

    number = std::abs(number);
    numbers_.push_back(number % module_);
    number /= module_;
    while (number != 0) {
        numbers_.push_back(number % module_);
        number /= module_;
    }
}

LongInteger::LongInteger(unsigned long long number) :
    signed_(false) {

    numbers_.push_back(number % module_);
    number /= module_;
    while (number != 0) {
        numbers_.push_back(number % module_);
        number /= module_;
    }
}

LongInteger &LongInteger::operator+=(const LongInteger &rhs) {
    std::cout << *this << " + " << rhs << std::endl;
    if (signed_ != rhs.signed_) {
        bool prev_signed = signed_;
        SubAsAbsoluteValues_(rhs);
        signed_ = prev_signed != signed_;
    }
    else {
        AddAsAbsoluteValues_(rhs);
    }
    return *this;
}

void LongInteger::AddAsAbsoluteValues_(const LongInteger &rhs) {
    auto max_size = std::max(numbers_.size(), rhs.numbers_.size());
    numbers_.resize(max_size + 1);
    auto this_it = numbers_.begin();
    auto remainder = 0ull;
    for (auto rhs_val : rhs.numbers_) {
        std::cout << "\t" << *this_it << " + " << rhs_val;
        *this_it += rhs_val + remainder;
        remainder = *this_it / module_;
        *this_it %= module_;
        std::cout << " = " << *this_it << std::endl;
        ++this_it;
    }
    while (remainder != 0) {
        *this_it += remainder;
        remainder = *this_it / module_;
        *this_it %= module_;
        ++this_it;
    }
    if (numbers_.back() == 0) {
        numbers_.pop_back();
    }
}

void LongInteger::SubAsAbsoluteValues_(const LongInteger &rhs) {
    auto max_size = std::max(numbers_.size(), rhs.numbers_.size());
    numbers_.resize(max_size);
    signed_ = false;
    auto this_it = numbers_.begin();
    auto remainder = 0ull;
    for (auto rhs_val : rhs.numbers_) {
        std::cout << "\t" << *this_it << " - " << rhs_val;
        auto current_remainder = remainder;
        remainder = *this_it < rhs_val + remainder ? 1 : 0;
        *this_it += module_ - rhs_val - current_remainder;
        *this_it %= module_;
        std::cout << " = " << *this_it << std::endl;
        ++this_it;
    }
    if (remainder != 0) {
        remainder = 0;
        auto rhs_it = rhs.numbers_.begin();
        for (auto &&val : numbers_) {
            val = module_ - val - remainder;
            std::cout << "\t(" << val << ")\n";
            remainder |= 1ull;
        }
        signed_ = true;
    }
    while (numbers_.back() == 0 && numbers_.size() > 0) {
        numbers_.pop_back();
    }
}

void LongInteger::Abs() noexcept {
    signed_ = false;
}

void LongInteger::Print(std::ostream &out) const {
    if (signed_) {
        out << "-";
    }
    auto it = numbers_.rbegin();
    out << *it;
    ++it;
    for (; it != numbers_.rend(); ++it) {
        out << std::setfill('0') << std::setw(n_digits_in_number_) << *it;
    }
}

bool LongInteger::Equal(const LongInteger &rhs) const {
    if (signed_ != rhs.signed_) {
        return false;
    }
    return numbers_ == rhs.numbers_;
}

bool LongInteger::Less(const LongInteger &rhs) const {
    if (signed_ && !rhs.signed_) {
        return true;
    }
    if (!signed_ && rhs.signed_) {
        return false;
    }
    if (signed_) {
        return numbers_ > rhs.numbers_;
    }
    return numbers_ < rhs.numbers_;
}

LongInteger operator+(const LongInteger &lhs, const LongInteger &rhs) {
    LongInteger res{lhs};
    res += rhs;
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
