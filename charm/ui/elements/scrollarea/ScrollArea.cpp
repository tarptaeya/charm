#include "ScrollArea.h"

namespace charm::ui {

#define SCROLLBAR_SIZE 15

ScrollArea::ScrollArea(Element* element)
    : m_element(element)
{
    set_is_width_expandable(true);
    set_is_height_expandable(true);
}

ScrollArea::~ScrollArea()
{
}

void ScrollArea::draw()
{
    Element::draw();

    m_element->set_bounds(m_x + m_shift_x, m_y, m_element->get_min_width(), m_element->get_min_height());
    m_element->set_clip(m_x, m_y, m_width, m_height);
    m_element->draw();

    auto& ui_context = Context::get_instance();

    if (m_element->get_min_width() > m_width) {
        Context::Rect left_button_rect(m_x, m_y + m_height - SCROLLBAR_SIZE, SCROLLBAR_SIZE, SCROLLBAR_SIZE);
        left_button_rect.set_color({ 0, 0, 0 });
        ui_context.add_rect(left_button_rect);

        Context::Rect right_button_rect(m_x + m_width - SCROLLBAR_SIZE, m_y + m_height - SCROLLBAR_SIZE, SCROLLBAR_SIZE, SCROLLBAR_SIZE);
        right_button_rect.set_color({ 0, 0, 0 });
        ui_context.add_rect(right_button_rect);
    }
}

void ScrollArea::set_bounds(float x, float y, float width, float height)
{
    Element::set_bounds(x, y, width, height);
    m_element->set_bounds(x, y, m_element->get_min_width(), m_element->get_min_height());
}

void ScrollArea::set_clip(float x, float y, float width, float height)
{
    Element::set_clip(x, y, width, height);
    m_element->set_clip(x, y, width, height);
}

void ScrollArea::on_mouse_button_callback(int button, int action, int mods)
{
    Element::on_mouse_button_callback(button, action, mods);

    if (m_is_mouse_just_pressed) {
        if (m_x <= m_mouse_x && m_mouse_x <= m_x + SCROLLBAR_SIZE && m_y + m_height - SCROLLBAR_SIZE <= m_mouse_y && m_mouse_y <= m_y + m_height) {
            m_shift_x += 10;
        }

        if (m_x + m_width - SCROLLBAR_SIZE <= m_mouse_x && m_mouse_x <= m_x + m_width && m_y + m_height - SCROLLBAR_SIZE <= m_mouse_y && m_mouse_y <= m_y + m_height) {
            m_shift_x -= 10;
        }
    }
}

}