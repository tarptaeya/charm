include_directories(../charm .)

add_executable(test_matrix4f test_matrix4f.cpp)
target_link_libraries(test_matrix4f charm)
add_test(NAME test_matrix4f COMMAND test_matrix4f)
