add_executable(solution solution.cpp)

target_link_libraries(
  solution
  PRIVATE
    eul
    project_options
    project_warnings
    fmt::fmt
    range-v3::range-v3)
