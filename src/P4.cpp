#include <eul/k_combinations.hpp>
#include <eul/is_palindrome.hpp>
#include <range/v3/view/filter.hpp>
#include <fmt/ranges.h>

int main()
{
  namespace rv = ranges::views;
  namespace stdr = std::ranges;

  constexpr auto bin_multiply = [](int a, int b){ return a * b; } ;
  
  auto product_combinations = eul::k_combinations<2>(100, 1000, bin_multiply);
  
  auto palindromes = product_combinations
                   | rv::filter(eul::is_palindrome);
  
  auto largest_palindrome = *stdr::max_element(palindromes);

  fmt::print("{}\n", largest_palindrome);
}
