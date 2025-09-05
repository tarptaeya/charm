#include "IRootWidget.h"
#include "Application.h"
#include "graphics/font/Font.h"

namespace charm {

void IRootWidget::add(ui::Element* element)
{
    m_children.push_back(element);
}

void IRootWidget::remove(ui::Element* element)
{
    auto it = std::find(m_children.begin(), m_children.end(), element);
    if (it == m_children.end())
        return;

    m_children.erase(it);
}

void IRootWidget::draw()
{
    float width = charmApp.get_width();
    float height = charmApp.get_height();

    auto& ui_context = ui::Context::get_instance();

    gl::Context::reset_framebuffer(GL_FRAMEBUFFER);
    gl::Context::viewport(0, 0, width, height);

    gl::Context::disable(GL_DEPTH_TEST);
    gl::Context::enable(GL_BLEND);
    gl::Context::blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gl::Context::active_texture(GL_TEXTURE0 + FONT_TEXTURE_UNIT);
    gl::Context::bind(GL_TEXTURE_2D, ui_context.get_font().get_texture());

    gl::Context::use(ui_context.get_program());
    gl::Context::set_uniform(ui_context.get_program(), "u_font_texture", FONT_TEXTURE_UNIT);
    gl::Context::set_uniform(ui_context.get_program(), "u_canvas_texture", CANVAS_TEXTURE_UNIT);
    gl::Context::set_uniform(ui_context.get_program(), "u_projection",
        Matrix4f({
            // clang-format off
                2.f / width, 0,               0, 0,
                0,             -2.f / height, 0, 0,
                0,             0,             1, 0,
                -1,            1,             0, 1,
            // clang-format on
        }));

    ui_context.begin();
    ui_context.add_rect(0, 0, width, height, { 0.9, 0.9, 0.9 }, 0, { 0, 0 }, { 0, 0 });

    float curr_y = 0;
    for (const auto& child : m_children) {
        float child_width = child->get_min_width();
        if (child->get_is_width_expandable()) {
            child_width = width;
        }
        child->set_bounds(0, curr_y, child_width, child->get_min_height());
        curr_y += child->get_min_height();
        child->draw();
    }

    ui_context.commit();

    gl::Context::disable(GL_BLEND);
    gl::Context::enable(GL_DEPTH_TEST);
}

}