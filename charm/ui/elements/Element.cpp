#include "Element.h"

namespace charm::ui {

float Element::get_min_width() const
{
    return m_min_width;
}

float Element::get_min_height() const
{
    return m_min_height;
}

bool Element::get_is_width_expandable() const
{
    return m_expand_width;
}

bool Element::get_is_height_expandable() const
{
    return m_expand_height;
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