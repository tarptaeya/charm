set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(
    font-conv
    main.cpp
)
target_link_libraries(font-conv charm)

add_executable(
    font-conv-sdf
    sdf.cpp
)
target_link_libraries(font-conv-sdf charm freetype)