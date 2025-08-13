#include "Application.h"
#include "IGameLoop.h"

namespace charm {

Application* Application::s_instance = nullptr;

Application::Application(const AppOptions& options)
{
    if (!glfwInit()) {
        std::cerr << "[error] glfw initialization faield" << std::endl;
        std::exit(0);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    m_window = glfwCreateWindow(options.window_width, options.window_height, options.window_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "[error] window creation failed" << std::endl;
        std::exit(0);
    }

    glfwMakeContextCurrent(m_window);
    gladLoadGL(glfwGetProcAddress);

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        charmApp->m_game_loop->on_key_input(key, scancode, action, mods);
    });
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
        charmApp->m_game_loop->on_mouse_button(button, action, mods);
    });

    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        charmApp->m_width = width;
        charmApp->m_height = height;
    });
}

Application::~Application()
{
    delete m_game_loop;
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

GLFWwindow* Application::get_window() const
{
    return m_window;
}

int Application::get_width() const
{
    return m_width;
}

int Application::get_height() const
{
    return m_height;
}

Registry<Shader>& Application::get_shader_registry()
{
    return m_shaders;
}

Registry<Program>& Application::get_program_registry()
{
    return m_programs;
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

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, m_width, m_height);
        m_game_loop->update(delta_time);

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
        std::exit(0);
    }
    return s_instance;
}

}