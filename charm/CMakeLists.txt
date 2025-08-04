add_library(
    charmcore
    app/Application.cpp
    app/Window.cpp
    camera/Camera.cpp
    ecs/components/MeshRendererComponent.cpp
    ecs/components/TransformComponent.cpp
    ecs/Component.cpp
    ecs/Entity.cpp
    graphics/geometry/BoxGeometry.cpp
    graphics/geometry/Geometry.cpp
    graphics/material/Material.cpp
    graphics/shaders/ShaderProgram.cpp
    graphics/shaders/ShaderRegistry.cpp
    graphics/textures/ImageData.cpp
    graphics/textures/Texture2D.cpp
    graphics/textures/Texture2DBuilder.cpp
    graphics/Renderer.cpp
    io/FileIO.cpp
    io/ppm/PPMReader.cpp
    math/Matrix4f.cpp
    math/Vector4f.cpp
)

target_link_libraries(charmcore glfw glad)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(charmcore PRIVATE DEBUG_BUILD)
endif()

install(TARGETS charmcore)
install(DIRECTORY . DESTINATION include/charm FILES_MATCHING PATTERN "*.h")