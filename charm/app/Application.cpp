#include "Application.h"
#include "AppAdapter.h"
#include "Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace charm {

Application* Application::s_instance = nullptr;

Application::Application(const AppOptions& options)
{
    if (!glfwInit()) {
        std::cerr << "[error] glfw initialization faield" << std::endl;
        std::exit(1);
    }

    m_window = new Window(options);
    glfwSetKeyCallback(m_window->m_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        charmApp->m_adapter->on_key_input(key, scancode, action, mods);
    });
    glfwSetMouseButtonCallback(m_window->m_handle, [](GLFWwindow* window, int button, int action, int mods) {
        charmApp->m_adapter->on_mouse_button(button, action, mods);
    });
}

Application::~Application()
{
    delete m_adapter;
    delete m_window;
    glfwTerminate();
}

Registry<Shader>& Application::get_shader_registry()
{
    return m_shaders;
}

Registry<Material>& Application::get_material_registry()
{
    return m_materials;
}

Registry<Geometry>& Application::get_geometry_registry()
{
    return m_geometries;
}

int Application::exec()
{
    double prev_time = glfwGetTime();
    while (!m_window->should_close()) {
        double curr_time = glfwGetTime();
        double delta_time = curr_time - prev_time;
        prev_time = curr_time;
        m_adapter->update(delta_time);

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