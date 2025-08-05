#include "XApplication.h"
#include "XAppAdapter.h"
#include "XWindow.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

XApplication* XApplication::s_instance = nullptr;

XApplication::XApplication(const XAppOptions& options)
{
    if (!glfwInit()) {
        std::cerr << "[error] glfw initialization faield" << std::endl;
        std::exit(1);
    }

    m_window = new XWindow(options);
    glfwSetKeyCallback(m_window->m_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        xApp->m_adapter->on_key_input(key, scancode, action, mods);
    });
}

XApplication::~XApplication()
{
    delete m_adapter;
    delete m_window;
    glfwTerminate();
}

XRegistry<XShader>& XApplication::get_shader_registry()
{
    return m_shaders;
}

XRegistry<XMaterial>& XApplication::get_material_registry()
{
    return m_materials;
}

int XApplication::exec()
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

XApplication* XApplication::get_instance()
{
    if (!s_instance) {
        std::cerr << "[error] no app instance created yet" << std::endl;
        std::exit(1);
    }
    return s_instance;
}
