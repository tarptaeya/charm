add_library(
    charm
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
    graphics/shaders/Program.cpp
    graphics/shaders/Shader.cpp
    graphics/textures/ImageData.cpp
    graphics/textures/Texture2D.cpp
    graphics/textures/Texture2DBuilder.cpp
    graphics/Renderer.cpp
    io/FileIO.cpp
    io/Input.cpp
    io/ppm/PPMReader.cpp
    math/Matrix4f.cpp
    math/Vector4f.cpp
)

target_link_libraries(charm glfw glad)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(charm PRIVATE DEBUG_BUILD)
endif()

install(TARGETS charm)
install(DIRECTORY . DESTINATION include/charm FILES_MATCHING PATTERN "*.h")