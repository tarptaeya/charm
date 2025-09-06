#include "Checkbox.h"
#include "charm.h"

namespace charm::ui {

#define BOX_BORDER_WIDTH 2
#define SPACE_BETWEEN_BOX_AND_LABEL 12

Checkbox::Checkbox(const std::string& text)
    : Element()
    , m_label(text)
{
}

Checkbox::~Checkbox()
{
}

void Checkbox::draw()
{
    Element::draw();

    auto& ui_context = Context::get_instance();

    Context::Rect outer_rect(m_x, m_y, get_box_size(), get_box_size());
    outer_rect.set_color({ 0, 0, 0 });
    ui_context.add_rect(outer_rect);

    Context::Rect inner_rect(m_x + BOX_BORDER_WIDTH, m_y + BOX_BORDER_WIDTH, get_box_size() - 2 * BOX_BORDER_WIDTH, get_box_size() - 2 * BOX_BORDER_WIDTH);
    inner_rect.set_color(charmApp.get_options().ui_background_color);
    ui_context.add_rect(inner_rect);

    if (m_value) {
        Context::Rect value_rect(m_x + 2 * BOX_BORDER_WIDTH, m_y + 2 * BOX_BORDER_WIDTH, get_box_size() - 4 * BOX_BORDER_WIDTH, get_box_size() - 4 * BOX_BORDER_WIDTH);
        value_rect.set_color({ 0, 0, 0 });
        ui_context.add_rect(value_rect);
    }

    m_label.draw();
}

float Checkbox::get_min_width() const
{
    return m_label.get_min_width() + get_box_size() + SPACE_BETWEEN_BOX_AND_LABEL;
}

float Checkbox::get_min_height() const
{
    return m_label.get_min_height();
}

void Checkbox::set_bounds(float x, float y, float width, float height)
{
    Element::set_bounds(x, y, width, height);

    float label_x_padding = get_box_size() + SPACE_BETWEEN_BOX_AND_LABEL;
    float label_y_padding = std::max(0.f, (height - m_label.get_min_height()) / 2);

    m_label.set_bounds(x + label_x_padding, y + label_y_padding, width - label_x_padding, height - 2 * label_y_padding);
}

Checkbox& Checkbox::set_text(const std::string& text)
{
    m_label.set_text(text);
    return *this;
}

void Checkbox::on_mouse_enter()
{
    charmApp.execute_on_frame_end(ON_ENTER_ELEMENT_PRIORITY, [] { charmApp.set_cursor(GLFW_HAND_CURSOR); });
}

void Checkbox::on_mouse_exit()
{
    charmApp.execute_on_frame_end(ON_EXIT_ELEMENT_PRIORITY, [] { charmApp.set_cursor(GLFW_ARROW_CURSOR); });
}

bool Checkbox::is_checked() const
{
    return m_value;
}

int Checkbox::get_box_size() const
{
    return m_height;
}

void Checkbox::on_mouse_button_callback(int button, int action, int mods)
{
    Element::on_mouse_button_callback(button, action, mods);

    if (m_is_mouse_just_pressed) {
        m_value = !m_value;
    }
}

}