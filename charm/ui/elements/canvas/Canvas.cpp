#include "Canvas.h"

namespace charm::ui {

Canvas::Canvas(Context& context, RenderTarget& render_target)
    : Element(context)
    , m_render_target(render_target)
{
    set_is_width_expandable(false);
    set_is_height_expandable(false);
}

void Canvas::draw()
{
    m_context.commit();

    gl::Context::active_texture(GL_TEXTURE0 + CANVAS_TEXTURE_UNIT);
    gl::Context::bind(GL_TEXTURE_2D, m_render_target.get_color_texture());
    m_context.begin();

    Element::draw();
    m_context.add_rect(m_x, m_y, m_width, m_height, { 0.1, 0.1, 0.1 }, 2, { 0, 1 }, { 1, 0 });
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