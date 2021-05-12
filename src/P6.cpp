#include <fmt/ranges.h>
#include <range/v3/view/iota.hpp> // views::ints
#include <range/v3/view/transform.hpp>
#include <range/v3/numeric/accumulate.hpp>

// https://projecteuler.net/problem=6

int main(){
  namespace r = ranges;
  namespace rv = r::views;

  auto square = [](int const e){ return e * e ;};
  auto sequence = rv::ints(1, 101);
  
  auto const sum_of_squares = r::accumulate(
    sequence | rv::transform(square), 0
  );
  
  auto const square_of_sum = square(r::accumulate(sequence, 0));

  fmt::print("{}\n", square_of_sum - sum_of_squares);
}