#ifndef ALGORITHMS_INCLUDE_ALGO_ARITHMETIC_H_
#define ALGORITHMS_INCLUDE_ALGO_ARITHMETIC_H_

#include <cmath>
#include <limits>
#include <type_traits>
#include <vector>

namespace arithmetic {

class LongInteger final {
public:
    LongInteger(long long number);
    
    explicit LongInteger(unsigned long long number);

    bool equal(const LongInteger &rhs) const;

    bool less(const LongInteger &rhs) const;

private:
    std::vector<unsigned long long> integers_;
    bool signed_;
};

bool operator<(const LongInteger &lhs, const LongInteger &rhs);

bool operator<=(const LongInteger &lhs, const LongInteger &rhs);

bool operator>(const LongInteger &lhs, const LongInteger &rhs);

bool operator>=(const LongInteger &lhs, const LongInteger &rhs);

bool operator==(const LongInteger &lhs, const LongInteger &rhs);

bool operator!=(const LongInteger &lhs, const LongInteger &rhs);

}  // namespace arithmetic

namespace algo {

namespace arithmetic {

template <class T, bool = std::is_class_v<T>>
struct ArithmeticConstants {
    constexpr static T unit() { return T::unit(); }
};

template <class T>
struct ArithmeticConstants<T, false> {
    constexpr static T unit() { return 1; }
};

template <class T, class TConstants = ArithmeticConstants<T>>
T FastPow(const T &val, unsigned pow) {
    auto result = TConstants::unit();
    if (pow == 0) {
        return result;
    }
    unsigned pow_mask = 1u << (std::numeric_limits<unsigned>::digits - 1);
    while (pow_mask != 0) {
        result *= result;
        if ((pow & pow_mask) != 0) {
            result *= val;
        } 
        pow_mask >>= 1;
    }
    return result;
}

}  // namespace arithmetic

}  // namespace algo

#endif  // ALGORITHMS_INCLUDE_ALGO_ARITHMETIC_H_
