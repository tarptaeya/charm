#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "XAppOptions.h"

class XWindow {
    friend class XApplication;
    GLFWwindow* m_handle = nullptr;

    explicit XWindow(const XAppOptions&);

public:
    ~XWindow();

    XWindow(const XWindow&) = delete;
    XWindow& operator=(const XWindow&) = delete;

    bool should_close();
    void swap_buffers();
};
