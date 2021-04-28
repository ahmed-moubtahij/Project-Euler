#include <fmt/core.h>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/filter.hpp>

// https://projecteuler.net/problem=1

int main(){
    namespace rnv = ranges::views;
    using rnv::iota, rnv::filter, ranges::accumulate;
    
    auto constexpr is_mult_of_3_or_5 = [](unsigned int n)
    { return n % 3u == 0u or n % 5u == 0u; };
    
    auto const result = accumulate(iota(3u, 1000u)
                                 | filter(is_mult_of_3_or_5),
                                   0u);
    fmt::print("{}", result);
}

