#include <fmt/core.h>
#include <range/v3/view/indices.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/partial_sum.hpp>
#include <range/v3/algorithm/find_if.hpp>
#include <eul/numbers_properties.hpp>

namespace r = ranges;
namespace rv = r::views;

template<std::unsigned_integral T>
[[nodiscard]]
auto triangle_nb_with_over_n_divisors(T n) noexcept -> T
{
  struct P{ T triangle_nb; T factors_count; };

  auto append_factors_count = [](T triangle_nb) -> P
  {
    return {
      triangle_nb,
      static_cast<T>(r::distance(
          rv::indices(T{ 1 }, triangle_nb + T{ 1 })
        | rv::filter(eul::divides{ triangle_nb })
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
  //constexpr unsigned n_divisors{ 300 }; // works
   constexpr unsigned n_divisors{ 500 }; // too much compile time; range-v3's fault
  
  fmt::print("{}\n",
    triangle_nb_with_over_n_divisors(n_divisors)
  );
}
