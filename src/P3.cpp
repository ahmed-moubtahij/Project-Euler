#include <fmt/core.h>
#include <set>
#include <cmath>

// https://projecteuler.net/problem=3

using primes_set = std::set<std::size_t>;

[[nodiscard]] constexpr
auto size_t_sqrt(std::size_t n)
{
  return static_cast<std::size_t>(std::sqrt(n));
}

constexpr
void insert_primes(primes_set& primes,
                   std::size_t n_to_factor,
                   std::size_t const prime_candidate,
                   std::size_t& upper_bound)
{
  while(n_to_factor % prime_candidate == 0)
  {
    primes.insert(prime_candidate);
    n_to_factor /= prime_candidate;
    upper_bound = size_t_sqrt(n_to_factor);
  }
}

int main(){
    primes_set primes;
    std::size_t const n{ 600'851'475'143 };
    
    // No need for divides by 2 since the given n is odd
    for(std::size_t odd{ 3 }, upper_bound = size_t_sqrt(n);
        odd <= upper_bound;
        odd += 2)
    {
      insert_primes(primes, n, odd, upper_bound);
    }
    fmt::print("{}\n", *primes.rbegin());
}
