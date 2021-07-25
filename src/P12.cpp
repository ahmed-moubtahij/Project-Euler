// NOTE: TIMES OUT ON GODBOLT, NEEDS TESTING ON VS
// https://godbolt.org/z/5sTzsxds4

#include <fmt/ranges.h>
#include <range/v3/view/indices.hpp>
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
  struct P{ T triangle_nb; T factors_count; };

  auto pair_with_factors_count = [](T n) -> P
  {
    auto factors =
      rv::indices(1u, n + 1u)
      | rv::filter([n](T const i){ return n % i == 0; });
    return {n, static_cast<T>(r::distance(std::move(factors)))};
  };
  
  auto triangles_with_factors_count =
    rv::indices
    | rv::partial_sum // triangle numbers
    | rv::transform(std::move(pair_with_factors_count));

  return (*r::find_if(
    triangles_with_factors_count,
    [n](T const count){ return count > n; },
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
