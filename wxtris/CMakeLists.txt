
set(CMAKE_CXX_STANDARD 20)

file(GLOB WXTRIS_SRC "src/*.cpp")
add_executable(wxtris ${WXTRIS_SRC} )

target_link_libraries(wxtris trix wxWidgets::wxWidgets)

target_include_directories( wxtris PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
