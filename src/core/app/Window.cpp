#include "Window.h"

#include <iostream>

namespace charm {

Window::Window(const AppOptions& app_options)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    m_handle = glfwCreateWindow(app_options.window_width, app_options.window_height, app_options.window_title.c_str(), nullptr, nullptr);
    if (!m_handle) {
        std::cerr << "[error] window creation failed" << std::endl;
        std::exit(1);
    }

    glfwMakeContextCurrent(m_handle);
    gladLoadGL(glfwGetProcAddress);
}

bool Window::should_close()
{
    return glfwWindowShouldClose(m_handle);
}

void Window::swap_buffers()
{
    glfwSwapBuffers(m_handle);
}

}