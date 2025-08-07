#include "Application.h"
#include "AppAdapter.h"

namespace charm {

Application* Application::s_instance = nullptr;

Application::Application(const AppOptions& options)
{
    if (!glfwInit()) {
        std::cerr << "[error] glfw initialization faield" << std::endl;
        std::exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    m_window = glfwCreateWindow(options.window_width, options.window_height, options.window_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "[error] window creation failed" << std::endl;
        std::exit(1);
    }

    glfwMakeContextCurrent(m_window);
    gladLoadGL(glfwGetProcAddress);

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        charmApp->m_adapter->on_key_input(key, scancode, action, mods);
    });
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
        charmApp->m_adapter->on_mouse_button(button, action, mods);
    });
}

Application::~Application()
{
    delete m_adapter;
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

GLFWwindow* Application::get_window() const
{
    return m_window;
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
    while (!glfwWindowShouldClose(m_window)) {
        double curr_time = glfwGetTime();
        double delta_time = curr_time - prev_time;
        prev_time = curr_time;
        m_adapter->update(delta_time);

        glfwPollEvents();
        glfwSwapBuffers(m_window);
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