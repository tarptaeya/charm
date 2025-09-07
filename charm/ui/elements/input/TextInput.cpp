#include "TextInput.h"
#include "charm.h"

namespace charm::ui {

#define PADDING 5
#define BOX_BORDER_WIDTH 2

TextInput::TextInput()
    : m_label("")
{
    set_is_width_expandable(true);
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
    outer_rect.set_color({ 0, 0, 0 });
    ui_context.add_rect(outer_rect);

    Context::Rect inner_rect(m_x + BOX_BORDER_WIDTH, m_y + BOX_BORDER_WIDTH, m_width - 2 * BOX_BORDER_WIDTH, m_height - 2 * BOX_BORDER_WIDTH);
    inner_rect.set_color(charmApp.get_options().ui_background_color);
    ui_context.add_rect(inner_rect);

    m_label.draw();

    if (m_show_cursor) {
        float xcurr = m_label.m_x;
        for (int i = 0; i < m_cursor_pos; ++i) {
            auto chrect = Label::get_rect_for_char(m_label.get_text()[i], m_label.get_font_size());
            xcurr += chrect.advance;
        }

        Context::Rect cursor_rect(xcurr, m_y + 2 * BOX_BORDER_WIDTH, BOX_BORDER_WIDTH, m_height - 4 * BOX_BORDER_WIDTH);
        cursor_rect.set_color({ 0, 0, 0 });
        ui_context.add_rect(cursor_rect);
    }
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
    float label_x_padding = std::max(0.f, (width - m_label.get_min_width()) / 2);
    float label_y_padding = std::max(0.f, (height - m_label.get_min_height()) / 2);

    m_label.set_bounds(x + label_x_padding, y + label_y_padding, width - 2 * label_x_padding, height - 2 * label_y_padding);
}

void TextInput::set_clip(float x, float y, float width, float height)
{
    Element::set_clip(x, y, width, height);
    m_label.set_clip(x, y, width, height);
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

void TextInput::on_mouse_enter()
{
    charmApp.execute_on_frame_end(ON_ENTER_ELEMENT_PRIORITY, [] { charmApp.set_cursor(GLFW_IBEAM_CURSOR); });
}

void TextInput::on_mouse_exit()
{
    charmApp.execute_on_frame_end(ON_EXIT_ELEMENT_PRIORITY, [] { charmApp.set_cursor(GLFW_ARROW_CURSOR); });
}

void TextInput::on_char_callback(unsigned int codepoint)
{
    if (!m_is_active)
        return;

    if (codepoint > 127)
        return;

    char ch = static_cast<char>(codepoint);
    auto text = m_label.get_text();
    if (m_cursor_pos == text.size()) {
        text += ch;
    } else {
        text.insert(m_cursor_pos, 1, ch);
    }
    ++m_cursor_pos;
    m_label.set_text(text);
}

void TextInput::on_key_callback(int key, int scancode, int action, int mods)
{
    if (!m_is_active)
        return;

    if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        m_cursor_pos -= 1;
        m_show_cursor = true;
        m_cursor_time_so_far = 0;
        m_cursor_pos = std::max(0, m_cursor_pos);
    }

    if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        m_cursor_pos += 1;
        m_show_cursor = true;
        m_cursor_time_so_far = 0;
        m_cursor_pos = std::min(m_cursor_pos, (int)m_label.get_text().size());
    }

    if (key == GLFW_KEY_BACKSPACE && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        auto text = m_label.get_text();
        if (m_cursor_pos != 0) {
            --m_cursor_pos;
            text.erase(m_cursor_pos, 1);
        }
        m_label.set_text(text);
    }
}

void TextInput::on_cursor_pos_callback(double x, double y)
{
    Element::on_cursor_pos_callback(x, y);
}

void TextInput::on_mouse_button_callback(int button, int action, int mods)
{
    Element::on_mouse_button_callback(button, action, mods);

    if (m_is_mouse_just_pressed) {
        m_is_active = true;
        m_show_cursor = true;
        m_cursor_time_so_far = 0;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !m_is_mouse_hover) {
        m_is_active = false;
        m_show_cursor = false;
        m_cursor_time_so_far = 0;
    }
}

}