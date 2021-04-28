#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/for_each.hpp>
#include <concepts>

namespace eul{
// Returns a range of the unique products of
// the monotonically increasing integers in [from, to)
// Expected throughput of input (2, 4):
// [2, 3, 4) -> [ [2*2, 2*3], [3*3] ]
// Expected output: [4, 6, 9]
template<std::integral T>
[[nodiscard]]
auto unique_products(T from, T to) noexcept
{
  namespace rnv = ranges::views;

  auto const make_products_subrange = [to](T cur){
    return rnv::ints(cur, to)
         | rnv::transform([cur](T i){ return cur * i; });
  };
  
  return rnv::ints(from, to)
       | rnv::for_each(make_products_subrange);
}
}
