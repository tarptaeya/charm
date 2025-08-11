cmake_minimum_required(VERSION 4.0)

project(charm VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)


include_directories(deps/glfw/include deps/glad/include charm)

add_subdirectory(deps)
add_subdirectory(charm)
add_subdirectory(src)
add_subdirectory(tools)

enable_testing()
add_subdirectory(test)
