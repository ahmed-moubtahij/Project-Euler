#include <fmt/core.h>
#include <eul/is_prime.hpp> // eul::oddly_factorable
#include <range/v3/view/iota.hpp> // views::ints
#include <range/v3/view/stride.hpp>
#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/drop_exactly.hpp>

// https://projecteuler.net/problem=7

int main(){
  namespace r = ranges;
  namespace rv = r::views;

  int const count{ 10'001 }; 
  int const offset{ 2 }; // For the 1st prime (2) and for retaining last
  
  auto n_primes = rv::ints(3, r::unreachable)
                | rv::stride(2)
                | rv::remove_if(eul::oddly_factorable)
                | rv::drop_exactly(count - offset);
  
  fmt::print("{}\n", *r::begin(n_primes));
  
  // Thanks to killerbee13@includecpp
  // for suggesting ranges::drop and taking from the front
  // as opposed to ranges::take, eager void looping and views::take_last(1)-ing the back
}