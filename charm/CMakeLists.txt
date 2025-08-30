add_library(
    charm
    app/Application.cpp
    camera/Camera.cpp
    ch3db/ch3db.cpp
    gl/Buffer.cpp
    gl/Context.cpp
    gl/Program.cpp
    gl/Shader.cpp
    gl/Texture.cpp
    gl/VertexArray.cpp
    graphics/font/Font.cpp
    graphics/font/FontMetadata.cpp
    graphics/framebuffer/Framebuffer.cpp
    graphics/framebuffer/FramebufferBuilder.cpp
    graphics/geometry/Geometry.cpp
    io/BinaryIO.cpp
    io/FileIO.cpp
    math/Matrix4f.cpp
    math/Vector3f.cpp
    misc/misc.cpp
    misc/stb_image.cpp
    misc/TextureBuilder.cpp
    ui/Context.cpp
    ui/Document.cpp
    ui/elements/Element.cpp
    ui/elements/button/Button.cpp
    ui/elements/hboxcontainer/HBoxContainer.cpp
    ui/elements/label/Label.cpp
    ui/elements/paddedcontainer/PaddedContainer.cpp
)

target_link_libraries(charm glfw glad)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(charm PRIVATE DEBUG_BUILD)
endif()

install(TARGETS charm)
install(DIRECTORY . DESTINATION include/charm FILES_MATCHING PATTERN "*.h")