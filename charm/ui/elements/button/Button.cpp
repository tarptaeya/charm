#include "Button.h"
#include "charm.h"

namespace charm::ui {

Button::Button(const std::string& text)
    : Element()
    , m_label(text)
{
}

Button::~Button()
{
}

void Button::draw()
{
    Element::draw();

    auto& ui_context = Context::get_instance();

    Context::Rect rect(m_x, m_y, m_width, m_height);
    rect.set_color(m_is_mouse_hover ? m_style.button_active_color : m_style.button_color)
        .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
    ui_context.add_rect(rect);

    m_label.set_clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
    m_label.draw();
}

float Button::get_min_width() const
{
    return m_label.get_min_width();
}

float Button::get_min_height() const
{
    return m_label.get_min_height();
}

void Button::set_bounds(float x, float y, float width, float height)
{
    Element::set_bounds(x, y, width, height);
    float label_x_padding = std::max(0.f, (width - m_label.get_min_width()) / 2);
    float label_y_padding = std::max(0.f, (height - m_label.get_min_height()) / 2);

    m_label.set_bounds(x + label_x_padding, y + label_y_padding, width - 2 * label_x_padding, height - 2 * label_y_padding);
}

Button& Button::set_on_click_handler(std::function<void(InputEventMouseButton&)> on_click)
{
    m_on_click = on_click;
    return *this;
}

Button& Button::set_text(const std::string& text)
{
    m_label.set_text(text);
    return *this;
}

void Button::on_cursor_pos_callback(InputEventMouseMotion& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_cursor_pos_callback(event);
    if (m_is_mouse_hover) {
        event.set_cursor_shape(GLFW_HAND_CURSOR);
    }
}

void Button::on_mouse_button_callback(InputEventMouseButton& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_mouse_button_callback(event);
    if (m_is_mouse_just_pressed) {
        m_on_click(event);
    }
}

void Button::set_style(const Style& style)
{
    m_style = style;

    Style other_style = style;
    other_style.text_color = style.button_text_color;
    m_label.set_style(other_style);
}

}