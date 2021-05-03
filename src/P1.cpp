#include <fmt/core.h>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/filter.hpp>

// https://projecteuler.net/problem=1

int main(){
    namespace r = ranges;
    namespace rv = r::views;
    
    constexpr auto is_mult_of_3_or_5 = [](int n)
    { return n % 3 == 0 or n % 5 == 0; };
    
    auto const result = r::accumulate(rv::ints(3, 1000)
                                    | rv::filter(is_mult_of_3_or_5),
                                      0u);
    fmt::print("{}\n", result);
}