#include "UIElement.h"

namespace charm {

float UIElement::get_min_width() const
{
    return m_min_width;
}

float UIElement::get_min_height() const
{
    return m_min_height;
}

bool UIElement::get_is_width_expandable() const
{
    return m_expand_width;
}

bool UIElement::get_is_height_expandable() const
{
    return m_expand_height;
}

float UIElement::get_width() const
{
    return m_width;
}

float UIElement::get_height() const
{
    return m_height;
}

void UIElement::set_bounds(float x, float y, float width, float height)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}

}