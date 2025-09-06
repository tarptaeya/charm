#include "IRootWidget.h"
#include "Application.h"
#include "graphics/font/Font.h"

namespace charm {

void IRootWidget::draw(ui::Element* element, float x, float y, float width, float height)
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
        Matrix4f({
            // clang-format off
                2.f / window_width, 0,               0, 0,
                0,             -2.f / window_height, 0, 0,
                0,             0,             1, 0,
                -1,            1,             0, 1,
            // clang-format on
        }));

    ui_context.begin();

    ui_context.add_rect(x, y, width, height, charmApp.get_options().ui_background_color, 0, { 0, 0 }, { 0, 0 });
    element->set_bounds(x, y, width, height);
    element->draw();
    ui_context.commit();

    gl::Context::disable(GL_BLEND);
    gl::Context::enable(GL_DEPTH_TEST);
}

}