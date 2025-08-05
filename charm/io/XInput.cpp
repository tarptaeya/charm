#include "XInput.h"
#include "app/XApplication.h"
#include "app/XWindow.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

bool XInput::is_key_pressed(int key)
{
    return glfwGetKey(xApp->m_window->m_handle, key) == GLFW_PRESS;
}