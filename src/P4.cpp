#include <eul/k_combinations.hpp>
#include <eul/is_palindrome.hpp>
#include <range/v3/view/filter.hpp>
#include <fmt/core.h>

int main()
{
  namespace rv = ranges::views;
  namespace stdr = std::ranges;

  constexpr auto bin_multiply =
  [](int const a, int const b){ return a * b; } ;
  
  auto palindromes = eul::k_combinations<2>(100, 1000, bin_multiply)
                   | rv::filter(eul::is_palindrome);
  
  fmt::print("{}\n", *stdr::max_element(palindromes));
}
