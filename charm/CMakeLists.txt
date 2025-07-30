add_library(
    charmcore
    app/Application.cpp
    app/Window.cpp
    ecs/Component.cpp
    ecs/Entity.cpp
    graphics/shaders/ShaderProgram.cpp
    graphics/shaders/ShaderRegistry.cpp
    io/FileIO.cpp
    math/Matrix4f.cpp
)

target_link_libraries(charmcore glfw glad)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(charmcore PRIVATE DEBUG_BUILD)
endif()