#ifndef ALGORITHMS_INCLUDE_ALGO_ARITHMETIC_H_
#define ALGORITHMS_INCLUDE_ALGO_ARITHMETIC_H_

#include <cmath>
#include <limits>
#include <type_traits>

namespace algo {

namespace arithmetic {

template <class T, bool = std::is_class_v<T>>
struct ArithmeticTraits {
  constexpr static T identity() { return T::unit(); }
};

template <class T>
struct ArithmeticTraits<T, false> {
  constexpr static T identity() { return 1; }
};

template <class T, class TTraits = ArithmeticTraits<T>>
constexpr T FastPow(const T &val, unsigned pow) {
  auto result = TTraits::identity();
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
