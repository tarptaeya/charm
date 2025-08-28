#include "HBoxContainer.h"

namespace charm::ui {

HBoxContainer::HBoxContainer(ImmediateUI& context)
    : Element(context)
{
}

HBoxContainer::~HBoxContainer()
{
}

void HBoxContainer::draw()
{
    Element::draw();

    for (const auto& child : m_children) {
        child->draw();
    }
}

float HBoxContainer::get_min_width() const
{
    float min_width = 0;
    for (const auto& child : m_children) {
        min_width += child->get_min_width();
    }
    return min_width;
}

float HBoxContainer::get_min_height() const
{
    float min_height = 0;
    for (const auto& child : m_children) {
        min_height = std::max(min_height, child->get_min_height());
    }
    return min_height;
}

bool HBoxContainer::get_is_width_expandable() const
{
    return true;
}

bool HBoxContainer::get_is_height_expandable() const
{
    return true;
}

void HBoxContainer::set_bounds(float x, float y, float width, float height)
{
    Element::set_bounds(x, y, width, height);

    int num_child = m_children.size();
    float child_width = m_width / num_child;
    float xcursor = x;
    for (const auto& child : m_children) {
        child->set_bounds(xcursor, y, child_width, m_height);
        xcursor += child_width;
    }
}

}