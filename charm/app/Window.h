#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "AppOptions.h"

namespace charm {

class Window {
    friend class Application;
    GLFWwindow* m_handle = nullptr;

    explicit Window(const AppOptions&);

public:
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool should_close();
    void swap_buffers();
};

}