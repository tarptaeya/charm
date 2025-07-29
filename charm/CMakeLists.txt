add_library(
    charmcore
    app/Application.cpp
    app/Window.cpp
    ecs/Component.cpp
    ecs/Entity.cpp
)

target_link_libraries(charmcore glfw glad)