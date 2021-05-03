#include <fmt/ranges.h>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/take_while.hpp>
#include <algorithm>

// https://projecteuler.net/problem=5

int main(){
  namespace r = ranges;
  namespace rv = r::views;
  namespace stdr = std::ranges;

  auto any_div_remainder = [](int e)
  {
    return stdr::any_of(
      rv::ints(1, 21),
      [e](int i){ return e % i != 0; }
    );
  };

  auto range = rv::ints(1, r::unreachable)
             | rv::take_while(any_div_remainder);

  // Adding one because views::iota is half-open
  auto answer = *stdr::max_element(range) + 1; 

  fmt::print("{}\n", answer);
}