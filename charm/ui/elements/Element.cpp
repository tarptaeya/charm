#include "Element.h"

namespace charm::ui {

Element::Element(ImmediateUI& context)
    : m_context(context)
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