#include "InputEventMouseMotion.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace charm {

InputEventMouseMotion::InputEventMouseMotion(double x, double y)
    : InputEvent()
    , m_x(x)
    , m_y(y)
{
    m_cursor_shape = GLFW_ARROW_CURSOR;
}

double InputEventMouseMotion::get_x() const
{
    return m_x;
}

double InputEventMouseMotion::get_y() const
{
    return m_y;
}

int InputEventMouseMotion::get_cursor_shape() const
{
    return m_cursor_shape;
}

void InputEventMouseMotion::set_cursor_shape(int shape)
{
    m_cursor_shape = shape;
}

}