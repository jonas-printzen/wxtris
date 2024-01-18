
function(pzen_validate target)
  target_compile_options(${target} PUBLIC -std=c++20 -O3)
  target_link_options(${target} PUBLIC -std=c++20 -O3)

  file( GLOB ${target}_TEST_SRC ${CMAKE_CURRENT_LIST_DIR}/test/*.cpp )

  add_executable( ${target}_test ${${target}_TEST_SRC} )
  find_package(GTest REQUIRED)
  target_link_libraries( ${target}_test ${target} gtest::gtest )

  # Enable GTest, which provides coverage data
  set( GTEST_RUN_FLAGS --gtest_color=yes STRING "Flags passed to GTest" )
  add_test( NAME ${target}_test COMMAND ${target}_test )

  add_custom_target(test_${target} ALL
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${target}_test
    DEPENDS ${target}_test
    # Need ./test/data
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )

endfunction()
