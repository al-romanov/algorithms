#ifndef ALGORITHMS_INCLUDE_ALGO_ARITHMETIC_H_
#define ALGORITHMS_INCLUDE_ALGO_ARITHMETIC_H_

#include <cmath>
#include <limits>
#include <type_traits>

namespace algo::arithmetic {

template<class T, bool = std::is_class_v<T>> struct ArithmeticTraits {
  constexpr static T identity() { return T::unit(); }
  constexpr static void multiply(T &dst, const T &src) { dst.mul(src); }
};

template<class T> struct ArithmeticTraits<T, false> {
  constexpr static T identity() { return 1; }
  constexpr static void multiply(T &dst, T src) { dst *= src; }
};

template<class T, class TTraits = ArithmeticTraits<T>>
constexpr T FastPow(const T &val, unsigned pow) {
  auto result = TTraits::identity();
  if (pow == 0) { return result; }
  auto pow_mask = 1U << (std::numeric_limits<unsigned>::digits - 1);
  while (pow_mask != 0) {
    TTraits::multiply(result, result);
    if ((pow & pow_mask) != 0) { TTraits::multiply(result, val); }
    pow_mask >>= 1;
  }
  return result;
}

}  // namespace algo::arithmetic

#endif  // ALGORITHMS_INCLUDE_ALGO_ARITHMETIC_H_
