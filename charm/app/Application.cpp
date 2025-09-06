#include "Application.h"
#include "IRootWidget.h"
#include "graphics/font/Font.h"
#include "io/FileIO.h"

namespace charm {

Application::~Application()
{
    if (m_window)
        glfwDestroyWindow(m_window);
    if (m_cursor)
        glfwDestroyCursor(m_cursor);
    glfwTerminate();
}

void Application::initialize(const AppOptions& options)
{
    m_options = options;
    if (!options.validate()) {
        std::cerr << "[error] app options provided are not valid" << std::endl;
        std::exit(0);
    }

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
    gl::Context::init(glfwGetProcAddress);

    glfwGetFramebufferSize(m_window, &m_width, &m_height);
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

const AppOptions& Application::get_options() const
{
    return m_options;
}

int Application::exec(IRootWidget* root_widget)
{
    m_root_widget_unowned_ptr = root_widget;

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        charmApp.m_root_widget_unowned_ptr->on_key_callback(key, scancode, action, mods);
    });

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        charmApp.m_width = width;
        charmApp.m_height = height;
    });

    double prev_time = glfwGetTime();
    while (!glfwWindowShouldClose(m_window)) {
        double curr_time = glfwGetTime();
        double delta_time = curr_time - prev_time;
        prev_time = curr_time;

        gl::Context::reset_framebuffer(GL_FRAMEBUFFER);
        root_widget->update(delta_time);
        root_widget->draw();

        std::sort(m_functions_to_execute_on_frame_end.begin(), m_functions_to_execute_on_frame_end.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
        for (const auto& [_priority, function] : m_functions_to_execute_on_frame_end) {
            function();
        }
        m_functions_to_execute_on_frame_end.clear();

        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    return 0;
}

Application& Application::get_instance()
{
    static Application application;
    return application;
}

void Application::set_cursor(int shape)
{
    if (m_cursor)
        glfwDestroyCursor(m_cursor);

    m_cursor = glfwCreateStandardCursor(shape);
    glfwSetCursor(m_window, m_cursor);
}

void Application::execute_on_frame_end(int priority, const std::function<void()>& function)
{
    m_functions_to_execute_on_frame_end.push_back({ priority, function });
}

}