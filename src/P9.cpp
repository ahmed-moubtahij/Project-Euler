#include <utility> // std::move
#include <eul/k_combinations.hpp> // eul::k_cartesian
#include <range/v3/view/filter.hpp>
#include <concepts> // std::same_as
#include <tuple> // std::apply
#include <fmt/core.h>

int main()
{
  namespace r = ranges;
  namespace rv = r::views;

  constexpr int sum{ 1000 };

  constexpr auto expected_pythagorean_sum =
  [](auto const common_tuple)
  {
    auto [a, b, c] = std::move(common_tuple);
    return (a*a + b*b == c*c) and (a + b + c == sum);
  };

  auto pythagorean_triplets = eul::k_cartesian<3>(1, sum + 1)
                            | rv::filter(expected_pythagorean_sum);

  constexpr auto fold_multiply =
  [](std::same_as<int> auto const ...is)
  { return (is * ... * 1); };

  constexpr auto tuple_fold =
  [fold_multiply](auto const common_tuple)
  { return std::apply(fold_multiply, std::move(common_tuple)); };

  fmt::print("{}\n", tuple_fold(*r::begin(pythagorean_triplets)));
}