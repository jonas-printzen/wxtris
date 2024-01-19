
# All files in the source-dir included in build!
file(GLOB WIDGETS_SRC src/*.cpp )

add_library(trix ${WIDGETS_SRC} )

target_link_libraries(trix PUBLIC wxWidgets::wxWidgets )

target_include_directories( trix PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

pzen_validate(trix)
