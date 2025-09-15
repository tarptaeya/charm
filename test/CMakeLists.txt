include_directories(../charm .)

add_executable(test_mat4 test_mat4.cpp)
target_link_libraries(test_mat4 charm)
add_test(NAME test_mat4 COMMAND test_mat4)
