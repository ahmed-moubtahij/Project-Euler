#include <range/v3/view/iota.hpp> // views::ints
#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/stride.hpp>
#include <range/v3/view/take_while.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <fmt/core.h>
#include <cstdint> // std::uint64_t
#include <eul/is_prime.hpp> // eul::oddly_factorable

// https://projecteuler.net/problem=10

int main()
{
  namespace r = ranges;
  namespace rv = r::views;
  using u64 = std::uint64_t;

  constexpr int upper_bound{ 2'000'000 };

  constexpr auto lt_upper_bound = [](int p)
  { return p < upper_bound; };

  auto primes = rv::ints(3, r::unreachable)
              | rv::stride(2)
              | rv::remove_if(eul::oddly_factorable)
              | rv::take_while(lt_upper_bound);

  fmt::print("{}\n", 2 + r::accumulate(primes, u64{ 0 }));
}