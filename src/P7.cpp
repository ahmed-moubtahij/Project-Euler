#include <eul/is_prime.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/take_while.hpp>
#include <fmt/core.h>

// https://projecteuler.net/problem=7

int main(){
  namespace r = ranges;
  namespace rv = r::views;

  int count{ 10'001 }, cache_prime;

  auto seeking_nth_prime = [&count, &cache_prime](int const i)
  {
    if(eul::is_prime(i))
    {
      cache_prime = i;
      --count;
    } 
    return count != 0; 
  };
  
  auto primes = rv::ints(2, r::unreachable)
              | rv::take_while(seeking_nth_prime);
  
  for(auto _ : primes) (void)_; // Trigger the lazy range
  
  fmt::print("{}\n", cache_prime); // Pick up the cache_prime side-effect
}