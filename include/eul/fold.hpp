#ifndef EUL_FOLD_HPP
#define EUL_FOLD_HPP

#include <range/v3/numeric/accumulate.hpp>
#include <eul/types_utility.hpp> // eul::tuple_like
#include <utility> // std::move
#include <concepts>
#include <tuple> // std::apply

namespace eul{

namespace fold{

  struct product_fn
  {
    [[nodiscard]] constexpr
    auto operator()(std::integral auto i,
                    std::integral auto ...is) const
    {
      return (i * ... * is);
    }

    template<ranges::range R>
    [[nodiscard]] constexpr
    auto operator()(R range) const
    {
      using value_t = ranges::range_value_t<R>;
      
      return ranges::accumulate(
        std::move(range),
        value_t{ 1 },
        [](value_t a, value_t b){ return a * b; }
      );
    }

    [[nodiscard]] constexpr
    auto operator()(tuple_like auto tuple) const
    {
      return std::apply(*this, std::move(tuple));
    }

  }; // !struct product_fn

  inline constexpr product_fn product;

} // !namespace fold

} // !namespace eul

#endif // !EUL_FOLD_HPP