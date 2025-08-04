add_library(
    charm
    app/XApplication.cpp
    app/XWindow.cpp
    camera/XCamera.cpp
    ecs/components/XMeshRendererComponent.cpp
    ecs/components/XTransformComponent.cpp
    ecs/XComponent.cpp
    ecs/XEntity.cpp
    graphics/geometry/XBoxGeometry.cpp
    graphics/geometry/XGeometry.cpp
    graphics/material/XMaterial.cpp
    graphics/shaders/XProgram.cpp
    graphics/shaders/XShaderRegistry.cpp
    graphics/textures/XImageData.cpp
    graphics/textures/XTexture2D.cpp
    graphics/textures/XTexture2DBuilder.cpp
    graphics/XRenderer.cpp
    io/XFileIO.cpp
    io/ppm/XPPMReader.cpp
    math/XMatrix4f.cpp
    math/XVector4f.cpp
)

target_link_libraries(charm glfw glad)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(charm PRIVATE DEBUG_BUILD)
endif()

install(TARGETS charm)
install(DIRECTORY . DESTINATION include/charm FILES_MATCHING PATTERN "*.h")