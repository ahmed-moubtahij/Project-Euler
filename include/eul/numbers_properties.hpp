#ifndef NUMBERS_PROPERTIES_HPP
#define NUMBERS_PROPERTIES_HPP

#include <concepts>

namespace eul{
  template<std::integral T>
  struct divides{
    T m;
    [[nodiscard]] constexpr
    auto operator()(T const i) const -> bool
    { return m % i == 0; }
  };

  template<std::integral T>
  struct greater_than{
    T m;
    [[nodiscard]] constexpr
    auto operator()(T const i) const -> bool
    { return i > m; }
  };
  template<typename T>
  greater_than(T m) -> greater_than<T>;
  //Note: Otherwise gets T& for some reason @(VS16.10.4, gcc 10.3, -std=c++2a)
} // namespace eul

#endif // NUMBERS_PROPERTIES_HPP