#include <eul/k_combinations.hpp>
#include <eul/is_palindrome.hpp>
#include <range/v3/view/filter.hpp>
#include <fmt/core.h>

int main()
{
  namespace rv = ranges::views;
  namespace stdr = std::ranges;

  constexpr auto bin_multiply =
  [](int a, int b){ return a * b; } ;
  
  // TODO: This might be an outer_product i.e. cartesian_view + chunk_view
  // c.f. adsp podcast ep 1
  // e.g. https://numpy.org/doc/stable/reference/generated/numpy.outer.html
  auto palindromes = eul::k_combinations<2>(100, 1000, bin_multiply)
                   | rv::filter(eul::is_palindrome);
  
  fmt::print("{}\n", *stdr::max_element(palindromes));
}
