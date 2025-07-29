add_executable(main main.cpp)
target_link_libraries(main charmcore)

add_custom_target(run COMMAND main DEPENDS main WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})