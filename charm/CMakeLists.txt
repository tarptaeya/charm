add_library(
    charm
    app/Application.cpp
    app/AppAdapter.cpp
    camera/Camera.cpp
    ch3db/ch3db.cpp
    ecs/components/MeshRendererComponent.cpp
    ecs/components/TransformComponent.cpp
    ecs/Component.cpp
    ecs/Entity.cpp
    ecs/Renderer.cpp
    graphics/framebuffer/Framebuffer.cpp
    graphics/framebuffer/FramebufferBuilder.cpp
    graphics/geometry/Geometry.cpp
    graphics/shaders/Shader.cpp
    graphics/textures/Texture2D.cpp
    graphics/textures/Texture2DBuilder.cpp
    graphics/textures/stb_image.cpp
    io/BinaryIO.cpp
    io/FileIO.cpp
    math/Matrix4f.cpp
    math/Vector3f.cpp
    misc/misc.cpp
    ui/FontMetadata.cpp
    ui/imui.cpp
)

target_link_libraries(charm glfw glad)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(charm PRIVATE DEBUG_BUILD)
endif()

install(TARGETS charm)
install(DIRECTORY . DESTINATION include/charm FILES_MATCHING PATTERN "*.h")