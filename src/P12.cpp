// NOTE: TIMES OUT ON GODBOLT, NEEDS TESTING ON VS
// https://godbolt.org/z/Wqvr9Ex83

#include <fmt/ranges.h>
#include <range/v3/view/iota.hpp> // ranges::views::ints
#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/partial_sum.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <cstdint> // std::uint32_t

namespace r = ranges;
namespace rv = r::views;

template<typename T = std::uint32_t>
[[nodiscard]] constexpr
auto triangle_nb_with_over_n_divisors(unsigned n) noexcept
{
  using pair_t = std::pair<T, T>;
  auto pair_with_factors_count = [](T n) -> pair_t
  {
    auto factors =
      rv::ints(T{ 1 }, static_cast<T>(n + 1))
      | rv::filter([n](T const i){ return n % i == 0; });
    return {n, r::distance(std::move(factors))};
  };
  
  auto triangles_with_factors_count =
    rv::ints
    | rv::partial_sum // triangle numbers
    | rv::transform(std::move(pair_with_factors_count));

  auto [triangle_nb, factors_count] = *r::find_if(
    triangles_with_factors_count,
    [n](T const count){ return count > n; },
    &pair_t::second
  );

  return triangle_nb;
}

int main(){
  // constexpr unsigned n_divisors{ 5 }; // works
  constexpr unsigned n_divisors{ 500 };
  
  fmt::print("{}\n",
    triangle_nb_with_over_n_divisors(n_divisors)
  );
}
