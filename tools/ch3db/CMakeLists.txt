set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(
    ch3db-conv
    main.cpp
)
target_link_libraries(ch3db-conv assimp charm)