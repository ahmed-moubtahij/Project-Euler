function(add_and_link_executable target)
  add_executable(${target} ${ARGN})
  target_link_libraries(${target} PRIVATE
      eul
      project_options
      project_warnings
      fmt::fmt
      range-v3::range-v3)
endfunction()

function(magic_target target)
  add_and_link_executable(${target} ${target}.cpp)
endfunction()

magic_target(P1)
magic_target(P2)
magic_target(P3)
magic_target(P4)
