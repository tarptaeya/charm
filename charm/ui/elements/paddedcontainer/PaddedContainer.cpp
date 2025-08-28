#include "PaddedContainer.h"

namespace charm::ui {

PaddedContainer::PaddedContainer(ImmediateUI& context, float padding_left_right, float padding_top_bottom)
    : Element(context)
    , m_padding_left_right(padding_left_right)
    , m_padding_top_bottom(padding_top_bottom)
{
}

PaddedContainer::~PaddedContainer()
{
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
    return min_width;
}

float PaddedContainer::get_min_height() const
{
    float min_height = 0;
    for (const auto& child : m_children) {
        min_height += child->get_min_height();
    }
    return min_height;
}

bool PaddedContainer::get_is_width_expandable() const
{
    return true;
}

bool PaddedContainer::get_is_height_expandable() const
{
    return true;
}

void PaddedContainer::set_bounds(float x, float y, float width, float height)
{
    Element::set_bounds(x, y, width, height);

    int num_children = m_children.size();
    float child_width = m_width - m_padding_left_right * 2;
    float available_height = m_height - m_padding_top_bottom * 2;
    float child_height = available_height / num_children;
    float ycursor = y;
    for (const auto& child : m_children) {
        child->set_bounds(x + m_padding_left_right, ycursor + m_padding_top_bottom, child_width, child_height);
        ycursor += child_height;
    }
}

}