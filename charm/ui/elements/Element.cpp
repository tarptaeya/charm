#include "Element.h"
#include "charm.h"

namespace charm::ui {

Element::Element()
{
}

Element::Element(Element&& other)
{
    m_is_width_expandable = other.m_is_width_expandable;
    m_is_height_expandable = other.m_is_height_expandable;
    other.m_is_width_expandable = other.m_is_height_expandable = false;

    m_x = other.m_x;
    m_y = other.m_y;
    m_width = other.m_width;
    m_height = other.m_height;
    m_is_mouse_hover = other.m_is_mouse_hover;
    m_is_mouse_pressed = other.m_is_mouse_pressed;
    m_is_mouse_just_pressed = other.m_is_mouse_just_pressed;

    other.m_x = other.m_y = other.m_width = other.m_height = 0;
    other.m_is_mouse_hover = other.m_is_mouse_pressed = other.m_is_mouse_just_pressed = false;
}

Element& Element::operator=(Element&& other)
{
    if (this == &other)
        return *this;

    m_is_width_expandable = other.m_is_width_expandable;
    m_is_height_expandable = other.m_is_height_expandable;
    other.m_is_width_expandable = other.m_is_height_expandable = false;

    m_x = other.m_x;
    m_y = other.m_y;
    m_width = other.m_width;
    m_height = other.m_height;
    m_is_mouse_hover = other.m_is_mouse_hover;
    m_is_mouse_pressed = other.m_is_mouse_pressed;
    m_is_mouse_just_pressed = other.m_is_mouse_just_pressed;

    other.m_x = other.m_y = other.m_width = other.m_height = 0;
    other.m_is_mouse_hover = other.m_is_mouse_pressed = other.m_is_mouse_just_pressed = false;

    return *this;
}

void Element::draw()
{
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

void Element::set_clip(float x, float y, float width, float height)
{
    m_clip_x = x;
    m_clip_y = y;
    m_clip_width = width;
    m_clip_height = height;
}

void Element::add_clip(float x, float y, float width, float height)
{
    float x1 = std::max(m_clip_x, x);
    float x2 = std::min(m_clip_x + m_clip_width, x + width);

    float y1 = std::max(m_clip_y, y);
    float y2 = std::min(m_clip_y + m_clip_height, y + height);

    m_clip_x = x1;
    m_clip_y = y1;
    m_clip_width = std::max(0.0f, x2 - x1);
    m_clip_height = std::max(0.0f, y2 - y1);
}

void Element::on_cursor_pos_callback(InputEventMouseMotion& event)
{
    if (event.should_stop_propatation())
        return;

    m_mouse_x = event.get_x();
    m_mouse_y = event.get_y();

    bool prev_is_mouse_hover = m_is_mouse_hover;
    if (m_clip_x <= m_mouse_x && m_mouse_x <= m_clip_x + m_clip_width && m_clip_y <= m_mouse_y && m_mouse_y <= m_clip_y + m_clip_height) {
        m_is_mouse_hover = (m_x <= m_mouse_x && m_mouse_x <= m_x + m_width && m_y <= m_mouse_y && m_mouse_y <= m_y + m_height);
    } else {
        m_is_mouse_hover = false;
    }

    m_is_mouse_just_entered = m_is_mouse_just_exited = false;
    if (!prev_is_mouse_hover && m_is_mouse_hover) {
        m_is_mouse_just_entered = true;
    } else if (prev_is_mouse_hover && !m_is_mouse_hover) {
        m_is_mouse_just_exited = true;
    }
}

void Element::on_mouse_button_callback(InputEventMouseButton& event)
{
    if (event.should_stop_propatation())
        return;

    if (m_is_mouse_hover && event.get_button() == GLFW_MOUSE_BUTTON_LEFT && event.get_action() == GLFW_PRESS) {
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

}