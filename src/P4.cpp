#include <range/v3/view/iota.hpp> // ranges::views::ints
#include <range/v3/view/transform.hpp>
#include <range/v3/view/cartesian_product.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/filter.hpp>
#include <algorithm>
#include <fmt/ranges.h>

namespace rnv = ranges::views;

template<std::size_t K>
[[nodiscard]] constexpr
auto k_combinations(int from, int to, std::relation<int, int> auto bin_op) noexcept
{
  namespace rnv = ranges::views;

  auto const k_cartesian =
  [from, to]<std::size_t ...Is>(std::index_sequence<Is...>)
  {
    return rnv::cartesian_product((void(Is), rnv::ints(from, to))...);
  };
  
  auto const fold_tuple = [bin_op](auto common_tuple)
  { return std::apply(bin_op, std::move(common_tuple)); };
  
  return k_cartesian(std::make_index_sequence<K>())
       | rnv::transform(fold_tuple);
}

struct is_palindrome_fn
{
  constexpr auto operator()(std::integral auto n) const noexcept
  {
    auto const str = std::to_string(n);
    return std::ranges::equal(str, str | rnv::reverse);
  }
};

inline constexpr is_palindrome_fn is_palindrome{};

int main()
{
  auto product_combinations = k_combinations<2>(100, 1000, std::multiplies{});
  auto palindromes = product_combinations
                   | rnv::filter(is_palindrome);
  
  auto largest_palindrome = *std::ranges::max_element(palindromes);

  fmt::print("{}\n", largest_palindrome);
}
