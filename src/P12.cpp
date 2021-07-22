// NOTE: TIMES OUT ON GODBOLT, NEEDS TESTING ON VS
// https://godbolt.org/z/z5nWe1hWz

#include "fmt/ranges.h"
#include "range/v3/view/iota.hpp" // ranges::views::ints
#include "range/v3/view/transform.hpp"
#include "range/v3/view/filter.hpp"
#include <range/v3/view/partial_sum.hpp>
#include <range/v3/view/drop_while.hpp>
#include <range/v3/view/take_exactly.hpp>
#include <cstdint> // std::uint32_t
#include <algorithm>

namespace r = ranges;
namespace rv = r::views;

template<unsigned N, typename T = std::uint32_t>
constexpr auto triangle_nb_with_over_n_divisors() noexcept
{
    constexpr auto from = T{ 1 };
    
    auto triangle_numbers = rv::ints(from, r::unreachable)
                          | rv::partial_sum;

    auto pair_with_factors_length = [](T to_factor)
    {
        auto is_divisor = [to_factor](T const divider)
        { return to_factor % divider == 0; };

        auto factors = rv::ints(from, static_cast<T>(to_factor + 1))
                     | rv::filter(std::move(is_divisor));

        return std::make_pair(
            to_factor,
            ranges::distance(std::move(factors))
        );
    };
    
    auto length_lesser_than_N = [](auto const& pair){ return pair.second < N + 1; };
    
    auto found = std::move(triangle_numbers)
        | rv::transform(std::move(pair_with_factors_length))
        | rv::drop_while(std::move(length_lesser_than_N))
        | rv::take_exactly(1);

    auto [triangle_nb, its_factors_length] = *r::begin(found);

    return triangle_nb;
}

int main(){
    // constexpr unsigned n_divisors{ 5 }; // works
    constexpr unsigned n_divisors{ 500 };
    
    fmt::print("\n{}\n",
        triangle_nb_with_over_n_divisors<n_divisors>()
    );
}
