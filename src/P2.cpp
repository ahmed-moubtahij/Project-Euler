#include <fmt/core.h>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/generate.hpp>
#include <range/v3/view/take_while.hpp>
#include <range/v3/view/filter.hpp>
#include <cstdint>

// https://projecteuler.net/problem=2

int main(){
    namespace r = ranges;
    namespace rv = r::views;
    using u32 = uint32_t;

    constexpr auto is_even = [](u32 n){ return n % 2 == 0; };

    auto fibonacci = [p = std::pair{1u, 2u}] () mutable -> u32
    { 
      return std::exchange(
               p, {p.second, p.first + p.second}
             ).first;
    };

    constexpr auto lt_upper_bound = [](u32 n){ return n < 4'000'000; };

    fmt::print("{}\n",
      r::accumulate(
        rv::generate(fibonacci)
      | rv::take_while(lt_upper_bound)
      | rv::filter(is_even),
      u32{ 0 }
    ));
}
