#include "Panel.h"
#include "app/Application.h"

namespace charm::ui {

Panel::Panel(const Style& style)
{
    m_style = style;
}

Panel::~Panel()
{
    for (const auto& el : m_elements) {
        delete el;
    }
    m_elements.clear();
}

Panel::Panel(Panel&& other)
{
    m_style = other.m_style;
    m_root_element = other.m_root_element;
    m_elements = std::move(other.m_elements);
    m_elements.clear();
    other.m_root_element = nullptr;
}

Panel& Panel::operator=(Panel&& other)
{
    if (this == &other)
        return *this;

    m_style = other.m_style;
    m_root_element = other.m_root_element;
    m_elements = std::move(other.m_elements);
    m_elements.clear();
    other.m_root_element = nullptr;

    return *this;
}

void Panel::set_root(charm::observer_ptr<ui::Element> root)
{
    m_root_element = root;
}

void Panel::draw(float x, float y, float width, float height)
{
    float window_width = charmApp.get_width();
    float window_height = charmApp.get_height();

    auto& ui_context = ui::Context::get_instance();

    gl::Context::reset_framebuffer(GL_FRAMEBUFFER);
    gl::Context::viewport(0, 0, window_width, window_height);

    gl::Context::disable(GL_DEPTH_TEST);
    gl::Context::enable(GL_BLEND);
    gl::Context::blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gl::Context::active_texture(GL_TEXTURE0 + FONT_TEXTURE_UNIT);
    gl::Context::bind(GL_TEXTURE_2D, ui_context.get_font().get_texture());

    gl::Context::use(ui_context.get_program());
    gl::Context::set_uniform(ui_context.get_program(), "u_font_texture", FONT_TEXTURE_UNIT);
    gl::Context::set_uniform(ui_context.get_program(), "u_canvas_texture", CANVAS_TEXTURE_UNIT);
    gl::Context::set_uniform(ui_context.get_program(), "u_projection",
        // clang-format off
        Mat4({ 
            { 2.f / window_width, 0,                    0, -1 },
            { 0,                  -2.f / window_height, 0, 1 },
            { 0,                  0,                    1, 0 },
            { 0,                  0,                    0, 1 }         
        })
        // clang-format on

    );

    ui_context.begin();

    ui_context.add_rect(x, y, width, height, m_style.background_color, 0, { 0, 0 }, { 0, 0 });
    m_root_element->set_bounds(x, y, width, height);
    m_root_element->set_clip(x, y, width, height);
    m_root_element->draw();
    ui_context.commit();

    gl::Context::disable(GL_BLEND);
    gl::Context::enable(GL_DEPTH_TEST);
}

void Panel::update(double delta_time)
{
    m_root_element->update(delta_time);
}

void Panel::on_char_callback(InputEventChar& event)
{
    if (event.should_stop_propatation())
        return;

    m_root_element->on_char_callback(event);
}

void Panel::on_key_callback(InputEventKey& event)
{
    if (event.should_stop_propatation())
        return;

    m_root_element->on_key_callback(event);
}

void Panel::on_cursor_pos_callback(InputEventMouseMotion& event)
{
    if (event.should_stop_propatation())
        return;

    m_root_element->on_cursor_pos_callback(event);
}

void Panel::on_mouse_button_callback(InputEventMouseButton& event)
{
    if (event.should_stop_propatation())
        return;

    m_root_element->on_mouse_button_callback(event);
}

void Panel::on_scroll_callback(InputEventScroll& event)
{
    if (event.should_stop_propatation())
        return;

    m_root_element->on_scroll_callback(event);
}

}