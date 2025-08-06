#include "Input.h"
#include "app/Application.h"
#include "app/Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace charm {

bool Input::is_key_pressed(int key)
{
    return glfwGetKey(charmApp->m_window->m_handle, key) == GLFW_PRESS;
}

}