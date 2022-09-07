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

LongInteger &LongInteger::operator-=(const LongInteger &rhs) {
    return *this;
}

void LongInteger::AddAsAbsoluteValues_(const LongInteger &rhs) {
    auto max_size = std::max(numbers_.size(), rhs.numbers_.size());
    numbers_.resize(max_size + 1);
    auto remainder = 0ull;
    auto it = std::transform(rhs.numbers_.begin(), rhs.numbers_.end(),
        numbers_.begin(), numbers_.begin(), [&remainder](auto val1, auto val2)
    {
        auto res = val1 + val2 + remainder;
        remainder = res / module_;
        return res % module_;
    });
    std::transform(it, numbers_.end(), it, [&remainder](auto val) {
        auto res = val + remainder;
        remainder = res / module_;
        return res % module_;
    });
    if (numbers_.back() == 0) {
        numbers_.pop_back();
    }
}

void LongInteger::SubAsAbsoluteValues_(const LongInteger &rhs) {
    auto max_size = std::max(numbers_.size(), rhs.numbers_.size());
    numbers_.resize(max_size);
    signed_ = false;
    auto remainder = 0ull;
    std::transform(rhs.numbers_.begin(), rhs.numbers_.end(),
        numbers_.begin(), numbers_.begin(), [&remainder](auto val1, auto val2)
    {
        auto current_remainder = remainder;
        remainder = val2 < val1 + remainder ? 1 : 0;
        return (val2 + module_ - val1 - current_remainder) % module_;
    });
    if (remainder != 0) {
        ToComplement_();
        signed_ = true;
    }
    while (numbers_.back() == 0 && numbers_.size() > 1) {
        numbers_.pop_back();
    }
}

void LongInteger::ToComplement_() {
    auto it = numbers_.begin();
    *it = (module_ - *it) % module_;
    ++it;
    std::transform(it, numbers_.end(), it, [](auto val) {
        return module_ - val - 1;
    });
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
