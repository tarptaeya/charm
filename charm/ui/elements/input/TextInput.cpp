#include "TextInput.h"
#include "charm.h"

namespace charm::ui {

#define PADDING 5
#define BOX_BORDER_WIDTH 2

TextInput::TextInput()
    : m_label("")
{
}

TextInput::~TextInput()
{
}

std::string TextInput::get_value() const
{
    return m_label.get_text();
}

void TextInput::set_value(const std::string& value)
{
    m_label.set_text(value);
}

void TextInput::draw()
{
    Element::draw();

    auto& ui_context = Context::get_instance();

    Context::Rect outer_rect(m_x, m_y, m_width, m_height);
    outer_rect.set_color(m_style.input_outline_color)
        .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
    ui_context.add_rect(outer_rect);

    Context::Rect inner_rect(m_x + BOX_BORDER_WIDTH, m_y + BOX_BORDER_WIDTH, m_width - 2 * BOX_BORDER_WIDTH, m_height - 2 * BOX_BORDER_WIDTH);
    inner_rect.set_color(m_style.input_background_color)
        .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
    ui_context.add_rect(inner_rect);

    float cursor_x = m_label.m_x;
    float shift = 0;
    for (int i = 0; i < m_cursor_pos; ++i) {
        auto chrect = Label::get_rect_for_char(m_label.get_text()[i], m_label.get_font_size());
        cursor_x += chrect.advance;
    }

    while (shift + cursor_x > m_x + m_width - 2 * PADDING) {
        --shift;
    }

    if (m_show_cursor) {
        Context::Rect cursor_rect(cursor_x + shift, m_y + 2 * BOX_BORDER_WIDTH, BOX_BORDER_WIDTH, m_height - 4 * BOX_BORDER_WIDTH);
        cursor_rect.set_color(m_style.input_text_color)
            .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
        ui_context.add_rect(cursor_rect);
    }

    float label_y_padding = std::max(0.f, (m_height - m_label.get_min_height()) / 2);
    m_label.set_bounds(m_x + shift + BOX_BORDER_WIDTH + PADDING, m_y + label_y_padding, m_width, m_height - 2 * label_y_padding);
    m_label.set_clip(m_clip_x + BOX_BORDER_WIDTH + PADDING, m_clip_y, m_clip_width - BOX_BORDER_WIDTH - PADDING, m_clip_height);
    m_label.add_clip(m_x, m_y, m_width, m_height);
    m_label.draw();
}

float TextInput::get_min_width() const
{
    return 100 + 2 * PADDING;
}

float TextInput::get_min_height() const
{
    return 1.8 * m_label.get_font_size() + PADDING;
}

void TextInput::set_bounds(float x, float y, float width, float height)
{
    Element::set_bounds(x, y, width, height);

    float label_y_padding = std::max(0.f, (height - m_label.get_min_height()) / 2);
    m_label.set_bounds(x + BOX_BORDER_WIDTH + PADDING, y + label_y_padding, m_label.get_min_width(), height - 2 * label_y_padding);
}

void TextInput::update(double delta_time)
{
    if (!m_is_active)
        return;

    m_cursor_time_so_far += delta_time;
    if (m_cursor_time_so_far > 0.5) {
        m_cursor_time_so_far = 0;
        m_show_cursor = !m_show_cursor;
    }
}

void TextInput::on_char_callback(InputEventChar& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_char_callback(event);

    if (!m_is_active)
        return;

    if (event.get_codepoint() > 127)
        return;

    char ch = static_cast<char>(event.get_codepoint());
    auto text = m_label.get_text();
    if (m_cursor_pos == text.size()) {
        text += ch;
    } else {
        text.insert(m_cursor_pos, 1, ch);
    }
    ++m_cursor_pos;
    m_label.set_text(text);
}

void TextInput::on_key_callback(InputEventKey& event)
{
    if (event.should_stop_propatation())
        return;

    if (!m_is_active)
        return;

    if (event.get_key() == GLFW_KEY_LEFT && (event.get_action() == GLFW_PRESS || event.get_action() == GLFW_REPEAT)) {
        m_cursor_pos -= 1;
        m_show_cursor = true;
        m_cursor_time_so_far = 0;
        m_cursor_pos = std::max(0, m_cursor_pos);
        event.stop_propagation();
    }

    if (event.get_key() == GLFW_KEY_RIGHT && (event.get_action() == GLFW_PRESS || event.get_action() == GLFW_REPEAT)) {
        m_cursor_pos += 1;
        m_show_cursor = true;
        m_cursor_time_so_far = 0;
        m_cursor_pos = std::min(m_cursor_pos, (int)m_label.get_text().size());
        event.stop_propagation();
    }

    if (event.get_key() == GLFW_KEY_BACKSPACE && (event.get_action() == GLFW_PRESS || event.get_action() == GLFW_REPEAT)) {
        auto text = m_label.get_text();
        if (m_cursor_pos != 0) {
            --m_cursor_pos;
            text.erase(m_cursor_pos, 1);
        }
        m_label.set_text(text);
        event.stop_propagation();
    }

    if (event.get_key() == GLFW_KEY_A && event.get_action() == GLFW_PRESS && ((event.get_mods() & GLFW_MOD_SUPER) || (event.get_mods() & GLFW_MOD_CONTROL))) {
        // TODO: enable selection
        event.stop_propagation();
    }
}

void TextInput::on_cursor_pos_callback(InputEventMouseMotion& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_cursor_pos_callback(event);
    if (m_is_mouse_hover) {
        event.set_cursor_shape(GLFW_IBEAM_CURSOR);
    }
}

void TextInput::on_mouse_button_callback(InputEventMouseButton& event)
{
    if (event.should_stop_propatation())
        return;

    Element::on_mouse_button_callback(event);

    if (m_is_mouse_just_pressed) {
        m_is_active = true;
        m_show_cursor = true;
        m_cursor_time_so_far = 0;
    }

    if (event.get_button() == GLFW_MOUSE_BUTTON_LEFT && event.get_action() == GLFW_PRESS && !m_is_mouse_hover) {
        m_is_active = false;
        m_show_cursor = false;
        m_cursor_time_so_far = 0;
    }
}

void TextInput::set_style(const Style& style)
{
    m_style = style;

    Style other_style = style;
    other_style.text_color = style.input_text_color;
    m_label.set_style(other_style);
}

}