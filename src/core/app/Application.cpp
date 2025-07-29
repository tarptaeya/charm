#include "Application.h"
#include "Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <iostream>

namespace charm {

Application* Application::s_instance = nullptr;

Application::Application(const AppOptions& app_options)
    : m_app_options(app_options)
{
    if (!glfwInit()) {
        std::cerr << "[error] glfw initialization faield" << std::endl;
        std::exit(1);
    }

    m_window = new Window(app_options);
}

Application::~Application()
{
    delete m_window;
    glfwTerminate();
}

void Application::create(const AppOptions& app_options)
{
    if (s_instance) {
        std::cerr << "[error] app instance already exists" << std::endl;
        std::exit(1);
    }

    s_instance = new Application(app_options);
}

void Application::create()
{
    AppOptions options;
    create(options);
}

int Application::exec()
{
    while (!m_window->should_close()) {
        glfwPollEvents();
        m_window->swap_buffers();
    }

    delete this;
    return 0;
}

Application* Application::get_instance()
{
    if (!s_instance) {
        std::cerr << "[error] no app instance created yet" << std::endl;
        std::exit(1);
    }
    return s_instance;
}

}