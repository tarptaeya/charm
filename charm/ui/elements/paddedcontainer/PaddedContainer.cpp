#include "PaddedContainer.h"

namespace charm::ui {

PaddedContainer::PaddedContainer(float padding)
    : Element()
    , m_padding_left(padding)
    , m_padding_right(padding)
    , m_padding_top(padding)
    , m_padding_bottom(padding)
{
    set_is_width_expandable(true);
    set_is_height_expandable(true);
}

PaddedContainer::PaddedContainer(float padding_left_right, float padding_top_bottom)
    : Element()
    , m_padding_left(padding_left_right)
    , m_padding_right(padding_left_right)
    , m_padding_top(padding_top_bottom)
    , m_padding_bottom(padding_top_bottom)
{
    set_is_width_expandable(true);
    set_is_height_expandable(true);
}

PaddedContainer::PaddedContainer(float padding_left, float padding_right, float padding_top, float padding_bottom)
    : Element()
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

void PaddedContainer::add(Element* element)
{
    m_children.push_back(element);
}

void PaddedContainer::remove(Element* element)
{
    auto it = std::find(m_children.begin(), m_children.end(), element);
    if (it == m_children.end())
        return;

    m_children.erase(it);
}

void PaddedContainer::draw()
{
    Element::draw();

    for (const auto& child : m_children) {
        child->draw();
    }
}

float PaddedContainer::get_min_width() const
{
    float min_width = 0;
    for (const auto& child : m_children) {
        min_width = std::max(min_width, child->get_min_width());
    }
    return min_width + m_padding_left + m_padding_right;
}

float PaddedContainer::get_min_height() const
{
    float min_height = 0;
    for (const auto& child : m_children) {
        min_height += child->get_min_height();
    }
    return min_height + m_padding_top + m_padding_bottom;
}

void PaddedContainer::set_bounds(float x, float y, float width, float height)
{
    Element::set_bounds(x, y, width, height);

    int num_children = m_children.size();
    float child_width = width - (m_padding_left + m_padding_right);
    float available_height = height - (m_padding_top + m_padding_bottom);
    float child_height = available_height / num_children;
    float ycursor = y + m_padding_top;
    for (const auto& child : m_children) {
        child->set_bounds(x + m_padding_left, ycursor, child_width, child_height);
        ycursor += child_height;
    }
}

}