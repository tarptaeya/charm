#include "PaddedContainer.h"

namespace charm::ui {

PaddedContainer::PaddedContainer(Element* element, float padding)
    : Element()
    , m_element(element)
    , m_padding_left(padding)
    , m_padding_right(padding)
    , m_padding_top(padding)
    , m_padding_bottom(padding)
{
    set_is_width_expandable(true);
    set_is_height_expandable(true);
}

PaddedContainer::PaddedContainer(Element* element, float padding_left_right, float padding_top_bottom)
    : Element()
    , m_element(element)
    , m_padding_left(padding_left_right)
    , m_padding_right(padding_left_right)
    , m_padding_top(padding_top_bottom)
    , m_padding_bottom(padding_top_bottom)
{
    set_is_width_expandable(true);
    set_is_height_expandable(true);
}

PaddedContainer::PaddedContainer(Element* element, float padding_left, float padding_right, float padding_top, float padding_bottom)
    : Element()
    , m_element(element)
    , m_padding_left(padding_left)
    , m_padding_right(padding_right)
    , m_padding_top(padding_top)
    , m_padding_bottom(padding_bottom)
{
    set_is_width_expandable(true);
    set_is_height_expandable(true);
}

PaddedContainer::~PaddedContainer()
{
}

void PaddedContainer::draw()
{
    Element::draw();

    m_element->set_clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
    m_element->draw();
}

float PaddedContainer::get_min_width() const
{
    return m_element->get_min_width() + m_padding_left + m_padding_right;
}

float PaddedContainer::get_min_height() const
{
    return m_element->get_min_height() + m_padding_top + m_padding_bottom;
}

void PaddedContainer::set_bounds(float x, float y, float width, float height)
{
    Element::set_bounds(x, y, width, height);

    float child_width = width - (m_padding_left + m_padding_right);
    float available_height = height - (m_padding_top + m_padding_bottom);
    float child_height = available_height;

    m_element->set_bounds(x + m_padding_left, y + m_padding_top, child_width, child_height);
}

}