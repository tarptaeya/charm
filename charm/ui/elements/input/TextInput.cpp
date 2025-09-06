#include "TextInput.h"
#include "charm.h"

namespace charm::ui {

#define PADDING 5
#define BOX_BORDER_WIDTH 2

TextInput::TextInput()
{
}

TextInput::~TextInput()
{
}

std::string TextInput::get_value() const
{
    return m_value;
}

void TextInput::set_value(const std::string& value)
{
    m_value = value;
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
}

float TextInput::get_min_width() const
{
    return 100 + 2 * PADDING;
}

float TextInput::get_min_height() const
{
    return m_font_size + 2 * PADDING;
}

int TextInput::get_font_size() const
{
    return m_font_size;
}

void TextInput::set_font_size(int size)
{
    m_font_size = size;
}

void TextInput::update(double delta_time)
{
}

void TextInput::on_mouse_enter()
{
    charmApp.execute_on_frame_end(ON_ENTER_ELEMENT_PRIORITY, [] { charmApp.set_cursor(GLFW_IBEAM_CURSOR); });
}

void TextInput::on_mouse_exit()
{
    charmApp.execute_on_frame_end(ON_EXIT_ELEMENT_PRIORITY, [] { charmApp.set_cursor(GLFW_ARROW_CURSOR); });
}

void TextInput::on_key_callback(int key, int scancode, int action, int mods)
{
}

}