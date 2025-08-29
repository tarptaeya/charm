#include "HBoxContainer.h"

namespace charm::ui {

HBoxContainer::HBoxContainer(ImmediateUI& context)
    : Element(context)
{
    set_is_width_expandable(true);
    set_is_height_expandable(true);
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

void HBoxContainer::set_bounds(float x, float y, float width, float height)
{
    Element::set_bounds(x, y, width, height);

    int num_expandable = 0;
    for (const auto& child : m_children) {
        if (child->get_is_width_expandable())
            ++num_expandable;
    }

    float extra_width = std::max(0.f, width - get_min_width());
    float xcursor = x;
    for (const auto& child : m_children) {
        float child_width = child->get_min_width();
        float child_height = child->get_min_height();

        if (child->get_is_width_expandable()) {
            child_width += extra_width / num_expandable;
        }

        if (child->get_is_height_expandable()) {
            child_height = height;
        }

        float padding_top = (height - child_height) / 2;
        child->set_bounds(xcursor, y + padding_top, child_width, child_height);
        xcursor += child_width;
    }
}

}