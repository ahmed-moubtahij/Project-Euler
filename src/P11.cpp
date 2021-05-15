#include <range/v3/view/chunk.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/drop_exactly.hpp>
#include <range/v3/view/iota.hpp> // views::ints
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/sliding.hpp>
#include <range/v3/view/stride.hpp>
#include <range/v3/view/take_exactly.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/algorithm/max.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <fmt/ranges.h>
#include <eul/fold.hpp>
#include <array>
#include <concepts>
#include <cstdint> // std::uint64_t
#include <utility> // std::move

// https://projecteuler.net/problem=11

template<std::size_t D>
class Grid{
  using grid_t = std::array<int, D * D>;
  using sz_t = std::size_t;

  grid_t m_flat_grid;
  
  static constexpr auto sliding_window =
  [](sz_t const length)
  {
    return [length](auto chunk)
    {
      namespace rv = ranges::views;
      return std::move(chunk)
           | rv::sliding(length);
    };
  };

  public:

  template<std::same_as<int> ...Is>
  constexpr Grid(Is ...es)
    requires (sizeof...(es) == D * D)
  : m_flat_grid{ es... } 
  { }

  [[nodiscard]]
  auto horizontal_windows(sz_t const length) const
  {
    namespace rv = ranges::views;
    
    return m_flat_grid
         | rv::chunk(D)
         | rv::for_each(sliding_window(length));
  }

  // Look into avoiding transpose and joining ranges of stride(D)
  [[nodiscard]]
  auto vertical_windows(sz_t const length) const
  {
    namespace rv = ranges::views;

    auto const column_view =
    [&flat_grid = m_flat_grid](sz_t const i)
    {
      return flat_grid
           | rv::drop_exactly(i)
           | rv::stride(D);
    };

    return rv::ints(decltype(D){ 0 }, D) 
         | rv::transform(column_view)
         | rv::for_each(sliding_window(length));
  }
  
  // Nttp argument needed here for std::make_index_sequence
  template<sz_t L>
  [[nodiscard]]
  auto diagonal_windows() const
  {
    namespace rv = ranges::views;

    auto diagonal = [&flat_grid = m_flat_grid](sz_t const i)
    {
      return flat_grid
           | rv::drop_exactly(i)  // start of the stride
           | rv::stride(D - 1)    // diagonal strides
           | rv::take_exactly(L); // #strides
    };

    auto generate_diagonals = [diagonal]
    (sz_t const first_row_i, sz_t const target_row_i, auto row_op)
    {
      return rv::ints(first_row_i, target_row_i)
           | rv::for_each(row_op)
           | rv::transform(diagonal);
    };

    auto row_left_sequence = [](sz_t const row_i)
    {
      return rv::ints(
        row_i*D + L - 1, (row_i + 1)*D
      );
    };

    auto left_diagonals = generate_diagonals(
      0, D - (L - 1), row_left_sequence
    );

    auto row_right_sequence = [](sz_t const i)
    {
      return rv::generate_n(
              [n = sz_t{ 1 }, i]() mutable { return i*D - n++; },
              D - (L - 1)
            );
    };

    auto right_diagonals = generate_diagonals(
      1, D - 2, row_right_sequence
    );
    
    return rv::concat(
      left_diagonals, right_diagonals
    );
  }
};

int main()
{
  using grid_20 = Grid<20>;
  grid_20 const grid(
    8,  2,  22, 97, 38, 15, 0,  40, 0,  75, 4,  5,  7,  78, 52, 12, 50, 77, 91, 8,
    49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 4,  56, 62, 0,
    81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 3,  49, 13, 36, 65,
    52, 70, 95, 23, 4,  60, 11, 42, 69, 24, 68, 56, 1,  32, 56, 71, 37, 2,  36, 91,
    22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80,
    24, 47, 32, 60, 99, 3, 45, 2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50,
    32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70,
    67, 26, 20, 68, 2, 62, 12, 20, 95, 63, 94, 39, 63, 8, 40, 91, 66, 49, 94, 21,
    24, 55, 58, 5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72,
    21, 36, 23, 9, 75, 0, 76, 44, 20, 45, 35, 14, 0, 61, 33, 97, 34, 31, 33, 95,
    78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 3, 80, 4, 62, 16, 14, 9, 53, 56, 92,
    16, 39, 5, 42, 96, 35, 31, 47, 55, 58, 88, 24, 0, 17, 54, 24, 36, 29, 85, 57,
    86, 56, 0, 48, 35, 71, 89, 7, 5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58,
    19, 80, 81, 68, 5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 4, 89, 55, 40,
    4,  52, 8, 83, 97, 35, 99, 16, 7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66,
    88, 36, 68, 87, 57, 62, 20, 72, 3, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69,
    4,  42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8, 46, 29, 32, 40, 62, 76, 36,
    20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 4, 36, 16,
    20, 73, 35, 29, 78, 31, 90, 1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 5, 54,
    1,  70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 1, 89, 19, 67, 48
  );
  
  namespace r = ranges;
  namespace rv = r::views;

  auto fold_product_windows = [](auto windows)
  {
    return std::move(windows)
         | rv::transform(eul::fold::product);
  };
  
  constexpr std::size_t length{ 4 };

  auto folded_windows = rv::concat(
    fold_product_windows(grid.horizontal_windows(length)),
    fold_product_windows(grid.vertical_windows(length)),
    fold_product_windows(grid.diagonal_windows<length>())
  );

  fmt::print("{}\n", r::max(folded_windows));
}