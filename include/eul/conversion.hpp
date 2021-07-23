#ifndef EUL_CONVERSION_HPP
#define EUL_CONVERSION_HPP

namespace eul{

  // T is a parameter to allow the caller
  // to handle conversion & overflowing
  // in subsequent operations
  template<typename T = int>
  constexpr auto ctoi(char c) -> T
  {
	return static_cast<T>(c - '0');
  }

} // namespace eul

#endif // EUL_CONVERSION_HPP
