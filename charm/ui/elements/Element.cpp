#include "Element.h"
#include "charm.h"

namespace charm::ui {

Element::Element(ImmediateUI& context)
    : m_context(context)
{
}

void Element::draw()
{
    double mouse_x, mouse_y;
    glfwGetCursorPos(charmWindow, &mouse_x, &mouse_y);

    m_is_mouse_hover = (m_x <= mouse_x && mouse_x <= m_x + m_width && m_y <= mouse_y && mouse_y <= m_y + m_height);

    if (m_is_mouse_hover && glfwGetMouseButton(charmWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (!m_is_mouse_just_pressed && !m_is_mouse_pressed)
            m_is_mouse_just_pressed = true;
        else
            m_is_mouse_just_pressed = false;

        m_is_mouse_pressed = true;
    } else {
        m_is_mouse_just_pressed = false;
        m_is_mouse_pressed = false;
    }
}

float Element::get_min_width() const
{
    return 0;
}

float Element::get_min_height() const
{
    return 0;
}

bool Element::get_is_width_expandable() const
{
    return false;
}

bool Element::get_is_height_expandable() const
{
    return false;
}

float Element::get_width() const
{
    return m_width;
}

float Element::get_height() const
{
    return m_height;
}

void Element::set_bounds(float x, float y, float width, float height)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}

}