#include "HBoxContainer.h"

namespace charm::ui {

HBoxContainer::~HBoxContainer()
{
}

void HBoxContainer::draw(ImmediateUI& api)
{
    int num_child = m_children.size();
    float child_width = m_width / num_child;
    float xcursor = m_x;
    for (const auto& child : m_children) {
        child->set_bounds(xcursor, m_y, child_width, m_height, api);
        child->draw(api);

        xcursor += child_width;
    }
}

float HBoxContainer::get_min_width(const ImmediateUI& api) const
{
    float min_width = 0;
    for (const auto& child : m_children) {
        min_width += child->get_min_width(api);
    }
    return min_width;
}

float HBoxContainer::get_min_height(const ImmediateUI& api) const
{
    float min_height = 0;
    for (const auto& child : m_children) {
        min_height = std::max(min_height, child->get_min_height(api));
    }
    return min_height;
}

bool HBoxContainer::get_is_width_expandable(const ImmediateUI& api) const
{
    return true;
}

bool HBoxContainer::get_is_height_expandable(const ImmediateUI& api) const
{
    return true;
}

void HBoxContainer::set_bounds(float x, float y, float width, float height, const ImmediateUI& api)
{
    Element::set_bounds(x, y, width, height, api);
}

}