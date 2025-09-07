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

    m_element->set_bounds(m_x + m_shift_x, m_y + m_shift_y, m_element->get_min_width(), m_element->get_min_height());
    m_element->set_clip(m_x, m_y, m_width, m_height);
    m_element->draw();

    auto& ui_context = Context::get_instance();

    bool show_x_scrollbar = m_element->get_min_width() > m_width;
    bool show_y_scrollbar = m_element->get_min_height() > m_height;

    if (show_x_scrollbar) {
        Context::Rect left_button_rect(m_x, m_y + m_height - SCROLLBAR_SIZE, SCROLLBAR_SIZE, SCROLLBAR_SIZE);
        left_button_rect.set_color({ 0, 0, 0 })
            .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
        ui_context.add_rect(left_button_rect);

        if (show_y_scrollbar) {
            Context::Rect right_button_rect(m_x + m_width - 2 * SCROLLBAR_SIZE, m_y + m_height - SCROLLBAR_SIZE, SCROLLBAR_SIZE, SCROLLBAR_SIZE);
            right_button_rect.set_color({ 0, 0, 0 })
                .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
            ui_context.add_rect(right_button_rect);
        } else {
            Context::Rect right_button_rect(m_x + m_width - SCROLLBAR_SIZE, m_y + m_height - SCROLLBAR_SIZE, SCROLLBAR_SIZE, SCROLLBAR_SIZE);
            right_button_rect.set_color({ 0, 0, 0 })
                .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
            ui_context.add_rect(right_button_rect);
        }
    }

    if (show_y_scrollbar) {
        Context::Rect top_button_rect(m_x + m_width - SCROLLBAR_SIZE, m_y, SCROLLBAR_SIZE, SCROLLBAR_SIZE);
        top_button_rect.set_color({ 0, 0, 0 })
            .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
        ui_context.add_rect(top_button_rect);

        if (show_x_scrollbar) {
            Context::Rect bottom_button_rect(m_x + m_width - SCROLLBAR_SIZE, m_y + m_height - 2 * SCROLLBAR_SIZE, SCROLLBAR_SIZE, SCROLLBAR_SIZE);
            bottom_button_rect.set_color({ 0, 0, 0 })
                .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
            ui_context.add_rect(bottom_button_rect);
        } else {
            Context::Rect bottom_button_rect(m_x + m_width - SCROLLBAR_SIZE, m_y + m_height - SCROLLBAR_SIZE, SCROLLBAR_SIZE, SCROLLBAR_SIZE);
            bottom_button_rect.set_color({ 0, 0, 0 })
                .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
            ui_context.add_rect(bottom_button_rect);
        }
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

    bool show_x_scrollbar = m_element->get_min_width() > m_width;
    bool show_y_scrollbar = m_element->get_min_height() > m_height;

    if (m_is_mouse_just_pressed) {
        if (show_x_scrollbar) {
            if (m_x <= m_mouse_x && m_mouse_x <= m_x + SCROLLBAR_SIZE && m_y + m_height - SCROLLBAR_SIZE <= m_mouse_y && m_mouse_y <= m_y + m_height) {
                m_shift_x += 10;
            }

            if (show_y_scrollbar) {
                if (m_x + m_width - 2 * SCROLLBAR_SIZE <= m_mouse_x && m_mouse_x <= m_x + m_width - SCROLLBAR_SIZE && m_y + m_height - SCROLLBAR_SIZE <= m_mouse_y && m_mouse_y <= m_y + m_height) {
                    m_shift_x -= 10;
                }
            } else {
                if (m_x + m_width - SCROLLBAR_SIZE <= m_mouse_x && m_mouse_x <= m_x + m_width && m_y + m_height - SCROLLBAR_SIZE <= m_mouse_y && m_mouse_y <= m_y + m_height) {
                    m_shift_x -= 10;
                }
            }
        }

        if (show_y_scrollbar) {
            if (m_x + m_width - SCROLLBAR_SIZE <= m_mouse_x && m_mouse_x <= m_x + m_width && m_y <= m_mouse_y && m_mouse_y <= m_y + SCROLLBAR_SIZE) {
                m_shift_y += 10;
            }

            if (show_x_scrollbar) {
                if (m_x + m_width - SCROLLBAR_SIZE <= m_mouse_x && m_mouse_x <= m_x + m_width && m_y + m_height - 2 * SCROLLBAR_SIZE <= m_mouse_y && m_mouse_y <= m_y + m_height - SCROLLBAR_SIZE) {
                    m_shift_y -= 10;
                }
            } else {
                if (m_x + m_width - SCROLLBAR_SIZE <= m_mouse_x && m_mouse_x <= m_x + m_width && m_y + m_height - SCROLLBAR_SIZE <= m_mouse_y && m_mouse_y <= m_y + m_height) {
                    m_shift_y -= 10;
                }
            }
        }
    }
}

}