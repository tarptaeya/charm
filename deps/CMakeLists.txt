add_subdirectory(glfw)

add_library(glad glad/src/gl.c)
install(TARGETS glad)
install(DIRECTORY glad/include/glad DESTINATION include FILES_MATCHING PATTERN "*.h")

add_subdirectory(assimp)
add_subdirectory(freetype)