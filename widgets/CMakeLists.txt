
# All files in the source-dir included in build!
file(GLOB WIDGETS_SRC src/*.cpp )

add_library(widgets ${WIDGETS_SRC} )

target_link_libraries(widgets PUBLIC wxWidgets::wxWidgets )

target_include_directories( widgets PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

pzen_validate(widgets)
