#include <utility> // std::move
#include <eul/k_combinations.hpp> // eul::k_cartesian
#include <eul/fold.hpp>
#include <range/v3/view/filter.hpp>
#include <fmt/core.h>

int main()
{
  namespace r = ranges;
  namespace rv = r::views;

  constexpr int sum{ 1000 };

  constexpr auto expected_pythagorean_sum =
  [](auto common_tuple)
  {
    auto [a, b, c] = std::move(common_tuple);
    return (a*a + b*b == c*c) and (a + b + c == sum);
  };

  auto pythagorean_tuples = eul::k_cartesian<3>(1, sum + 1)
                          | rv::filter(expected_pythagorean_sum);

  auto pythagorean_triplet = *r::begin(pythagorean_tuples);
  
  fmt::print("{}\n",  eul::fold::product(pythagorean_triplet));
}