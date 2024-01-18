
function(pzen_validate target)

    #### TODO: Break out separate build_type ######################
    # # Enable code coverage on provided target
    # target_compile_options(${target} PUBLIC -std=c++20 -coverage -fno-inline )
    # target_link_options(${target} PUBLIC -std=c++20 --coverage )

    # Regular debug-build
    target_compile_options(${target} PUBLIC -std=c++20 -fno-inline -g )
    target_link_options(${target} PUBLIC -std=c++20 -g )

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

    #### TODO: Break out separate build_type ######################
    # # Generate coverage report on provided target
    # add_custom_target(cov_${target} ALL
    #     COMMAND mkdir -p ${CMAKE_SOURCE_DIR}/cov
    #     COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --exclude ${CMAKE_CURRENT_SOURCE_DIR}/test --html --html-details --exclude-throw-branches --exclude-unreachable-branches --html-title "Coverage"  -o ${CMAKE_SOURCE_DIR}/cov/index.html ${target}
    #     # COMMAND find ${CMAKE_BINARY_DIR} -name "*.gc*" -delete
    #     DEPENDS test_${target}
    #     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    # )
endfunction()
