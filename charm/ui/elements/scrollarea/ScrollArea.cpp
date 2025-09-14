#include "ScrollArea.h"
#include "charm.h"

namespace charm::ui {

#define SCROLLBAR_SIZE 15
#define CONTENT_PADDING 2
#define SPEED 10

ScrollArea::ScrollArea(const charm::observer_ptr<Element>& element)
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

    bool show_x_scrollbar = m_element->get_min_width() > m_width;
    bool show_y_scrollbar = m_element->get_min_height() > m_height;

    m_shift_x = std::max(m_shift_x, m_width - m_element->get_min_width() - (show_y_scrollbar ? SCROLLBAR_SIZE + CONTENT_PADDING : 0));
    m_shift_x = std::min(m_shift_x, 0.0f);
    m_shift_y = std::max(m_shift_y, m_height - m_element->get_min_height() - (show_x_scrollbar ? SCROLLBAR_SIZE + CONTENT_PADDING : 0));
    m_shift_y = std::min(m_shift_y, 0.0f);

    m_element->set_bounds(m_x + m_shift_x, m_y + m_shift_y, m_element->get_min_width(), m_element->get_min_height());
    m_element->set_clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
    m_element->add_clip(m_x, m_y, m_width - (show_y_scrollbar ? SCROLLBAR_SIZE + CONTENT_PADDING : 0), m_height - (show_x_scrollbar ? SCROLLBAR_SIZE + CONTENT_PADDING : 0));
    m_element->draw();

    auto& ui_context = Context::get_instance();

    if (show_x_scrollbar) {
        Context::Rect handle_rect = get_horizontal_handle_rect();
        handle_rect.set_color(m_style.scroll_handle_color)
            .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
        ui_context.add_rect(handle_rect);
    }

    if (show_y_scrollbar) {
        Context::Rect handle_rect = get_vertical_handle_rect();
        handle_rect.set_color(m_style.scroll_handle_color)
            .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
        ui_context.add_rect(handle_rect);
    }
}

void ScrollArea::set_bounds(float x, float y, float width, float height)
{
    Element::set_bounds(x, y, width, height);
    m_element->set_bounds(x, y, m_element->get_min_width(), m_element->get_min_height());
}

float ScrollArea::get_min_width() const
{
    return 100;
}

float ScrollArea::get_min_height() const
{
    return 100;
}

void ScrollArea::update(double delta_time)
{
    m_element->update(delta_time);
}

void ScrollArea::on_char_callback(InputEventChar& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_char_callback(event);
    m_element->on_char_callback(event);
}

void ScrollArea::on_key_callback(InputEventKey& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_key_callback(event);
    m_element->on_key_callback(event);
}

void ScrollArea::on_cursor_pos_callback(InputEventMouseMotion& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_cursor_pos_callback(event);
    m_element->on_cursor_pos_callback(event);

    if (get_is_mouse_hover_horizontal_handle() || get_is_mouse_hover_vertical_handle()) {
        event.set_cursor_shape(GLFW_HAND_CURSOR);
    }

    if (m_is_horizontal_handle_dragged) {
        bool show_y_scrollbar = m_element->get_min_height() > m_height;

        float handle_container_width = m_width;
        if (show_y_scrollbar) {
            handle_container_width = m_width - SCROLLBAR_SIZE;
        }

        float dx = m_mouse_x - m_drag_prev_x;
        m_drag_prev_x = m_mouse_x;
        m_shift_x -= dx * m_element->get_min_width() / handle_container_width;
    }

    if (m_is_vertical_handle_dragged) {
        bool show_x_scrollbar = m_element->get_min_width() > m_width;

        float handle_container_height = m_height;
        if (show_x_scrollbar) {
            handle_container_height = m_height - SCROLLBAR_SIZE;
        }

        float dy = m_mouse_y - m_drag_prev_y;
        m_drag_prev_y = m_mouse_y;
        m_shift_y -= dy * m_element->get_min_height() / handle_container_height;
    }
}

void ScrollArea::on_mouse_button_callback(InputEventMouseButton& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_mouse_button_callback(event);

    bool show_x_scrollbar = m_element->get_min_width() > m_width;
    bool show_y_scrollbar = m_element->get_min_height() > m_height;

    if (m_is_mouse_just_pressed) {
        if (get_is_mouse_hover_horizontal_handle()) {
            m_is_horizontal_handle_dragged = true;
            m_drag_prev_x = m_mouse_x;
        }
        if (get_is_mouse_hover_vertical_handle()) {
            m_is_vertical_handle_dragged = true;
            m_drag_prev_y = m_mouse_y;
        }
    }

    if (!m_is_mouse_pressed) {
        m_is_horizontal_handle_dragged = false;
        m_is_vertical_handle_dragged = false;
    }

    m_element->on_mouse_button_callback(event);
}

void ScrollArea::on_scroll_callback(InputEventScroll& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_scroll_callback(event);
    m_element->on_scroll_callback(event);

    if (m_is_mouse_hover && !event.should_stop_propatation()) {
        m_shift_x += event.get_xoffset() * SPEED;
        m_shift_y += event.get_yoffset() * SPEED;
        event.stop_propagation();
    }
}

bool ScrollArea::get_is_mouse_hover_horizontal_handle() const
{
    bool show_x_scrollbar = m_element->get_min_width() > m_width;

    if (show_x_scrollbar) {
        auto rect = get_horizontal_handle_rect();
        return rect.x <= m_mouse_x && m_mouse_x <= rect.x + rect.width && rect.y <= m_mouse_y && m_mouse_y <= rect.y + rect.height;
    }

    return false;
}

bool ScrollArea::get_is_mouse_hover_vertical_handle() const
{
    bool show_y_scrollbar = m_element->get_min_height() > m_height;

    if (show_y_scrollbar) {
        auto rect = get_vertical_handle_rect();
        return rect.x <= m_mouse_x && m_mouse_x <= rect.x + rect.width && rect.y <= m_mouse_y && m_mouse_y <= rect.y + rect.height;
    }

    return false;
}

Context::Rect ScrollArea::get_horizontal_handle_rect() const
{
    bool show_x_scrollbar = m_element->get_min_width() > m_width;
    bool show_y_scrollbar = m_element->get_min_height() > m_height;

    float handle_container_width = m_width;
    float handle_size = m_width / m_element->get_min_width() * handle_container_width;

    if (show_y_scrollbar) {
        handle_container_width = m_width - SCROLLBAR_SIZE;
        handle_size = (m_width - SCROLLBAR_SIZE) / m_element->get_min_width() * handle_container_width;
    }

    Context::Rect handle_rect(m_x - handle_container_width * m_shift_x / m_element->get_min_width(), m_y + m_height - SCROLLBAR_SIZE, handle_size, SCROLLBAR_SIZE);
    return handle_rect;
}

Context::Rect ScrollArea::get_vertical_handle_rect() const
{
    bool show_x_scrollbar = m_element->get_min_width() > m_width;
    bool show_y_scrollbar = m_element->get_min_height() > m_height;

    float handle_container_height = m_height;
    float handle_size = m_height / m_element->get_min_height() * handle_container_height;

    if (show_x_scrollbar) {
        handle_container_height = m_height - SCROLLBAR_SIZE;
        handle_size = (m_height - SCROLLBAR_SIZE) / m_element->get_min_height() * handle_container_height;
    }

    Context::Rect handle_rect(m_x + m_width - SCROLLBAR_SIZE, m_y - handle_container_height * m_shift_y / m_element->get_min_height(), SCROLLBAR_SIZE, handle_size);
    return handle_rect;
}

}