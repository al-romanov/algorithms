#include "algo/arithmetic.h"

namespace arithmetic {

LongInteger::LongInteger(long long number) :
    signed_(number < 0),
    integers_(1, std::abs(number)) {}

LongInteger::LongInteger(unsigned long long number) :
    signed_(true),
    integers_(1, number) {}

bool LongInteger::equal(const LongInteger &rhs) const {
    if (signed_ != rhs.signed_) {
        return false;
    }
    return integers_ == rhs.integers_;
}

bool LongInteger::less(const LongInteger &rhs) const {
    if (signed_ && !rhs.signed_) {
        return true;
    }
    if (!signed_ && rhs.signed_) {
        return false;
    }
    if (signed_) {
        return integers_ > rhs.integers_;
    }
    return integers_ < rhs.integers_;
}

bool operator<(const LongInteger &lhs, const LongInteger &rhs) {
    return lhs.less(rhs);
}

bool operator<=(const LongInteger &lhs, const LongInteger &rhs) {
    return !rhs.less(lhs);
}

bool operator>(const LongInteger &lhs, const LongInteger &rhs) {
    return rhs.less(lhs);
}

bool operator>=(const LongInteger &lhs, const LongInteger &rhs) {
    return !lhs.less(rhs);
}

bool operator==(const LongInteger &lhs, const LongInteger &rhs) {
    return lhs.equal(rhs);
}

bool operator!=(const LongInteger &lhs, const LongInteger &rhs) {
    return !lhs.equal(rhs);
}

}  // namespace arithmetic
