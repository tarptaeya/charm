add_library(
    charmcore
    app/Application.cpp
    app/Window.cpp
)

target_link_libraries(charmcore glfw glad)