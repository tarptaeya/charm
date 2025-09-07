#include "Canvas.h"

namespace charm::ui {

Canvas::Canvas(RenderTarget& render_target)
    : Element()
    , m_render_target(render_target)
{
    set_is_width_expandable(false);
    set_is_height_expandable(false);
}

void Canvas::draw()
{
    auto& ui_context = Context::get_instance();
    ui_context.commit();

    gl::Context::active_texture(GL_TEXTURE0 + CANVAS_TEXTURE_UNIT);
    gl::Context::bind(GL_TEXTURE_2D, m_render_target.get_color_texture());
    ui_context.begin();

    Element::draw();

    Context::Rect rect(m_x, m_y, m_width, m_height);
    rect.set_color({ 0, 0, 0 })
        .set_active_texture(CANVAS_TEXTURE_UNIT)
        .set_texcoords({ 0, 1 }, { 1, 0 })
        .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
    ui_context.add_rect(rect);
}

float Canvas::get_min_width() const
{
    return 256;
}

float Canvas::get_min_height() const
{
    return 256;
}

}