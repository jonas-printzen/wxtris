
set(CMAKE_CXX_STANDARD 20)

file(GLOB WXTRIS_SRC "*.cpp")
add_executable(wxtris ${WXTRIS_SRC} )

target_link_libraries(wxtris widgets wxWidgets::wxWidgets)

