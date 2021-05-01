#include <fmt/core.h>
#include <set>
#include <cmath>

// https://projecteuler.net/problem=3

int main(){
    std::set<std::size_t> primes;
    std::size_t const n{ 600'851'475'143 };
    auto const upper_bound = static_cast<std::size_t>(std::sqrt(n));

    // No need for divides by 2 as the given n0 is odd
    for(std::size_t n_to_factor{ n }, prime{ 3 };
        prime <= upper_bound; prime += 2)
    {
      for(; n_to_factor % prime == 0; n_to_factor /= prime)
        primes.insert(prime);
    }
    
    auto const result = *primes.rbegin();
    
    fmt::print("{}\n", result);
}
