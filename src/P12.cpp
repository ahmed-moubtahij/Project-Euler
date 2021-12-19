// https://godbolt.org/z/bPoP7Garn

#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/view/iota.hpp> // ranges::view::ints
#include <range/v3/view/generate.hpp>
#include <algorithm>
#include <fmt/core.h>

#define MOV(x) static_cast<std::remove_cvref_t<decltype(x)>&&>(x)
#define FWD(x) static_cast<decltype(x)&&>(x)

namespace e12{

namespace stdr = std::ranges;
namespace r = ranges;
namespace rv = r::views;
using u32 = std::uint32_t;

struct n_divisible_triangle_fn{

struct TDC{
  u32 triangle_number{};
  std::size_t divisors_count{};

  explicit constexpr TDC(u32 n)
  : triangle_number{ nth_triangle_nb(n) }
  , divisors_count{ count_divisors(triangle_number) }
  { }

  static constexpr auto nth_triangle_nb(u32 n) -> u32
  { return *r::fold_left_first(rv::ints(1u, n + 1u), std::plus{}); }
  
  static constexpr auto count_divisors(u32 value) -> u32
  {
    if (value == 1)
      return 1u;
    
    auto divides_value = [value](u32 i){ return value % i == 0; };
    return 2 + static_cast<u32>(
      stdr::count_if(rv::ints(2u, value), MOV(divides_value))); 
  }
}; // !struct TDC

[[nodiscard]] auto operator()(u32 n) const noexcept -> TDC
{
  auto tdcs_gen = rv::generate([n] mutable { return TDC(n++); });
  auto gt_n = [n](u32 const divs_count){ return divs_count > n; };
  return *stdr::find_if(tdcs_gen, MOV(gt_n), &TDC::divisors_count);
}

}; // !struct n_divisible_triangle_fn

inline constexpr n_divisible_triangle_fn n_divisible_triangle;

} // !namespace e12

int main(){
  auto [triangle_nb, divisors_count] = e12::n_divisible_triangle(310);
  fmt::print("{}: {}\n", triangle_nb, divisors_count);
}
