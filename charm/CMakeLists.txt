add_library(
    charmcore
    app/Application.cpp
    app/Window.cpp
    ecs/Component.cpp
    ecs/Entity.cpp
    graphics/shaders/ShaderProgram.cpp
    graphics/shaders/ShaderRegistry.cpp
    graphics/textures/ImageData.cpp
    graphics/textures/Texture2D.cpp
    graphics/textures/Texture2DBuilder.cpp
    io/FileIO.cpp
    io/ppm/PPMReader.cpp
    math/Matrix4f.cpp
)

target_link_libraries(charmcore glfw glad)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(charmcore PRIVATE DEBUG_BUILD)
endif()