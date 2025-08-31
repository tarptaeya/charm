#include "Application.h"
#include "AppAdapter.h"
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

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    });
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
    });

    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        charmApp.m_width = width;
        charmApp.m_height = height;
    });

    set_font(options.font_texture_path, options.font_metadata_path);
    m_ui_program = gl::Context::create_program(FileIO::read_text(options.ui_vertex_shader_path), FileIO::read_text(options.ui_fragment_shader_path));
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

Font& Application::get_font()
{
    if (!m_font) {
        std::cerr << "[error] font is not set" << std::endl;
        std::exit(0);
    }

    return *m_font.get();
}

void Application::set_font(const std::string& texture_path, const std::string& metadata_path)
{
    m_font = std::make_unique<Font>(texture_path, metadata_path);
}

void Application::draw_document(ui::Document& document)
{
    gl::Context::viewport(0, 0, m_width, m_height);

    gl::Context::disable(GL_DEPTH_TEST);
    gl::Context::enable(GL_BLEND);
    gl::Context::blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gl::Context::use(m_ui_program);
    gl::Context::set_uniform(m_ui_program, "u_font_texture", 1);
    gl::Context::set_uniform(m_ui_program, "u_texture", 2);
    gl::Context::set_uniform(m_ui_program, "u_projection",
        Matrix4f({
            // clang-format off
                2.f / m_width, 0,               0, 0,
                0,             -2.f / m_height, 0, 0,
                0,             0,               1, 0,
                -1,            1,               0, 1,
            // clang-format on
        }));

    document.draw(0, 0, m_width, m_height);

    gl::Context::disable(GL_BLEND);
    gl::Context::enable(GL_DEPTH_TEST);
}

}