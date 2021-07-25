#include <fmt/ranges.h>
#include <range/v3/view/indices.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/partial_sum.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <cstdint> // std::uint32_t

namespace r = ranges;
namespace rv = r::views;

// TODO: Move this to include/eul/
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
}

template<typename T = std::uint32_t>
[[nodiscard]] constexpr
auto triangle_nb_with_over_n_divisors(unsigned n) noexcept
{
  struct P{ T triangle_nb; T factors_count; };

  auto append_factors_count = [](T n) -> P
  {
    return {n,
      static_cast<T>(r::distance(
          rv::indices(1u, n + 1u)
        | rv::filter(eul::divides{ n })
      ))
    };
  };
  
  auto triangles_with_factors_count =
    rv::indices
    | rv::partial_sum // triangle numbers
    | rv::transform(std::move(append_factors_count));

  return (*r::find_if(
    triangles_with_factors_count,
    eul::greater_than{ n },
    &P::factors_count
  )).triangle_nb;
}

int main(){
  constexpr unsigned n_divisors{ 5 }; // works
  // constexpr unsigned n_divisors{ 500 };
  
  fmt::print("{}\n",
    triangle_nb_with_over_n_divisors(n_divisors)
  );
}
