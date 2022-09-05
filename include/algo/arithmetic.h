#ifndef ALGORITHMS_INCLUDE_ALGO_ARITHMETIC_H_
#define ALGORITHMS_INCLUDE_ALGO_ARITHMETIC_H_

#include <iostream>
#include <limits>
#include <type_traits>

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
    std::cout << pow_mask << std::endl;
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
