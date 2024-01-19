cmake_minimum_required(VERSION 3.27)

project( wxtris VERSION 0.1.0 LANGUAGES CXX )
find_package(wxWidgets REQUIRED)

set(CMAKE_BUILD_TOOL_OPTIONS -j16)

include(cmake/${CMAKE_BUILD_TYPE}.cmake)

enable_testing()

add_subdirectory(widgets)
add_subdirectory(wxtris)

#==== GENERATING FILE FOR CLANGD IN CODIUM =====================
# Have to include at least one of the deps-files...
include( ${CMAKE_BINARY_DIR}/generators/GTestConfig.cmake )
# Ugly hack to get items in list of wxWidgets inc-dirs
list( GET wxWidgets_INCLUDE_DIRS 0 wxWidgets_INCLUDE_DIR0 )
list( GET wxWidgets_INCLUDE_DIRS 1 wxWidgets_INCLUDE_DIR1 )
# Generate compile_flags.txt from conan-deps
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compile_flags.templ ${CMAKE_CURRENT_SOURCE_DIR}/compile_flags.txt)

