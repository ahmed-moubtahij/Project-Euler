add_executable(P1 P1.cpp)
add_executable(P2 P2.cpp)

set(LIBS
      eul
      project_options
      project_warnings
      fmt::fmt
      range-v3::range-v3)

target_link_libraries(
  P1
  PRIVATE
    ${LIBS})

target_link_libraries(
  P2
  PRIVATE
    ${LIBS})
