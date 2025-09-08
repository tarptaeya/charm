#include "VBoxContainer.h"

namespace charm::ui {

VBoxContainer::VBoxContainer()
    : Element()
{
    set_is_width_expandable(true);
    set_is_height_expandable(true);
}

VBoxContainer::~VBoxContainer()
{
}

void VBoxContainer::add(const charm::observer_ptr<Element>& element)
{
    m_children.push_back(element);
}

void VBoxContainer::remove(const charm::observer_ptr<Element>& element)
{
    auto it = std::find(m_children.begin(), m_children.end(), element);
    if (it == m_children.end())
        return;

    m_children.erase(it);
}

void VBoxContainer::draw()
{
    Element::draw();

    for (const auto& child : m_children) {
        child->set_clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
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
        float child_width = std::min(width, child->get_min_width());
        float child_height = child->get_min_height();

        if (child->get_is_width_expandable()) {
            child_width = width;
        }

        if (child->get_is_height_expandable()) {
            child_height += extra_height / num_expandable;
        }

        child->set_bounds(x, ycursor, child_width, child_height);
        ycursor += child_height;
    }
}

void VBoxContainer::on_char_callback(const InputEventChar& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_char_callback(event);
    for (const auto& child : m_children) {
        child->on_char_callback(event);
    }
}

void VBoxContainer::on_key_callback(const InputEventKey& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_key_callback(event);
    for (const auto& child : m_children) {
        child->on_key_callback(event);
    }
}

void VBoxContainer::on_cursor_pos_callback(const InputEventMouseMotion& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_cursor_pos_callback(event);
    for (const auto& child : m_children) {
        child->on_cursor_pos_callback(event);
    }
}

}