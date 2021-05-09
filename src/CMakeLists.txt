function(add_and_link_target target)
  add_executable(${target} ${ARGN})
  target_link_libraries(${target} PRIVATE
      eul
      project_options
      project_warnings
      fmt::fmt
      range-v3::range-v3)
endfunction()

function(magic_target target)
  add_and_link_target(${target} ${target}.cpp)
endfunction()

foreach(i RANGE 1 10)
  magic_target(P${i})
endforeach()