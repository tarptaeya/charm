#include "Element.h"
#include "charm.h"

namespace charm::ui {

Element::Element()
{
}

std::string Element::get_id() const
{
    return m_id;
}

Element& Element::set_id(const std::string& id)
{
    m_id = id;
    return *this;
}

Element* Element::get_element_by_id(const std::string& id)
{
    if (m_id == id)
        return this;

    for (const auto& child : m_children) {
        auto ans = child->get_element_by_id(id);
        if (ans)
            return ans;
    }
    return nullptr;
}

void Element::draw()
{
    double mouse_x, mouse_y;
    glfwGetCursorPos(charmWindow, &mouse_x, &mouse_y);

    bool prev_is_mouse_hover = m_is_mouse_hover;
    m_is_mouse_hover = (m_x <= mouse_x && mouse_x <= m_x + m_width && m_y <= mouse_y && mouse_y <= m_y + m_height);

    if (!prev_is_mouse_hover && m_is_mouse_hover) {
        on_mouse_enter();
    } else if (prev_is_mouse_hover && !m_is_mouse_hover) {
        on_mouse_exit();
    }

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
    return m_is_width_expandable;
}

Element& Element::set_is_width_expandable(bool is_expandable)
{
    m_is_width_expandable = is_expandable;
    return *this;
}

bool Element::get_is_height_expandable() const
{
    return m_is_height_expandable;
}

Element& Element::set_is_height_expandable(bool is_expandable)
{
    m_is_height_expandable = is_expandable;
    return *this;
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