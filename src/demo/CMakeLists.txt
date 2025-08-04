add_executable(demo main.cpp)
target_link_libraries(demo charm)

add_custom_target(run COMMAND demo DEPENDS demo WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})