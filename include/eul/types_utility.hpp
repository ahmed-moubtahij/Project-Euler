#ifndef EUL_TYPES_UTILITY_HPP
#define EUL_TYPES_UTILITY_HPP

#include <type_traits>
#include <tuple>
#include <concepts>

namespace eul{
  template<typename T>
  concept tuple_like = std::is_object<T>::value and requires(T t)
  {
    typename std::tuple_size<T>::type;
    typename std::tuple_element<0, std::remove_const_t<T>>::type;
    { std::get<0>(t) } -> std::convertible_to<typename std::tuple_element<0, T>::type const&>;
    //{ get<0>(t) } -> std::convertible_to<typename std::tuple_element<0, T>::type const&>;
  };
} // !namespace eul

#endif // !EUL_TYPES_UTILITY_HPP
