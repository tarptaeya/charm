cmake_minimum_required(VERSION 4.0)

project(charm VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)

include_directories(deps/glfw/include deps/glad/include)

add_subdirectory(deps)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)