#include "VBoxContainer.h"

namespace charm::ui {

VBoxContainer::VBoxContainer(Context& context)
    : Element(context)
{
    set_is_width_expandable(true);
    set_is_height_expandable(true);
}

VBoxContainer::~VBoxContainer()
{
}

void VBoxContainer::draw()
{
    Element::draw();

    for (const auto& child : m_children) {
        child->draw();
    }
}

float VBoxContainer::get_min_width() const
{
    float min_width = 0;
    for (const auto& child : m_children) {
        min_width = std::max(min_width, child->get_min_width());
    }
    return min_width;
}

float VBoxContainer::get_min_height() const
{
    float min_height = 0;
    for (const auto& child : m_children) {
        min_height += child->get_min_height();
    }
    return min_height;
}

void VBoxContainer::set_bounds(float x, float y, float width, float height)
{
    Element::set_bounds(x, y, width, height);

    int num_expandable = 0;
    for (const auto& child : m_children) {
        if (child->get_is_height_expandable())
            ++num_expandable;
    }

    float extra_height = std::max(0.f, height - get_min_height());
    float ycursor = y;
    for (const auto& child : m_children) {
        float child_width = child->get_min_width();
        float child_height = child->get_min_height();

        if (child->get_is_width_expandable()) {
            child_width = width;
        }

        if (child->get_is_height_expandable()) {
            child_height += extra_height / num_expandable;
        }

        float padding_left = (width - child_width) / 2;
        child->set_bounds(x + padding_left, ycursor, child_width, child_height);
        ycursor += child_height;
    }
}

}