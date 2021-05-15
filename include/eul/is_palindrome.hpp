#ifndef IS_PALINDROME
#define IS_PALINDROME

#include <string>
#include <concepts>
#include <algorithm>
#include <range/v3/view/reverse.hpp>

namespace eul{

struct is_palindrome_fn
{
  constexpr auto operator()(std::integral auto n) const noexcept
  {
    auto const str = std::to_string(n);
    return std::ranges::equal(
        str, str | ranges::views::reverse
    );
  }
};

inline constexpr is_palindrome_fn is_palindrome{};

} // namespace eul

#endif // !IS_PALINDROME