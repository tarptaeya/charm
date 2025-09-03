#include "Button.h"
#include "charm.h"

namespace charm::ui {

Button::Button(Context& context, const std::string& text)
    : Element(context)
    , m_label(context, text)
{
}

Button::~Button()
{
}

void Button::draw()
{
    Element::draw();

    if (m_is_mouse_hover) {
        m_context.add_rect(m_x, m_y, m_width, m_height, { 0.25, 0.55, 0.6 }, 0, { 0, 0 }, { 0, 0 });
    } else {
        m_context.add_rect(m_x, m_y, m_width, m_height, { 0.2, 0.5, 0.5 }, 0, { 0, 0 }, { 0, 0 });
    }

    m_label.draw();

    if (m_is_mouse_just_pressed) {
        m_on_click();
    }
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

Button& Button::set_on_click_handler(std::function<void()> on_click)
{
    m_on_click = on_click;
    return *this;
}

Button& Button::set_text(const std::string& text)
{
    m_label.set_text(text);
    return *this;
}

void Button::on_mouse_enter()
{
    charmApp.execute_on_frame_end(ON_ENTER_ELEMENT_PRIORITY, [] { charmApp.set_cursor(GLFW_HAND_CURSOR); });
}

void Button::on_mouse_exit()
{
    charmApp.execute_on_frame_end(ON_EXIT_ELEMENT_PRIORITY, [] { charmApp.set_cursor(GLFW_ARROW_CURSOR); });
}

}