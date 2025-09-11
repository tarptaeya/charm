#include "Label.h"
#include "charm.h"

namespace charm::ui {

Label::Label(const std::string& text)
    : Element()
    , m_text(text)
{
}

Label::~Label()
{
}

void Label::draw()
{
    Element::draw();

    float xcurr = m_x;
    float ycurr = m_y + m_font_size;

    auto& ui_context = Context::get_instance();
    auto& font_metadata = ui_context.get_font().get_metadata();

    for (char c : m_text) {
        auto chrect = get_rect_for_char(c, m_font_size);

        Context::Rect rect(chrect.x + xcurr, chrect.y + ycurr, chrect.width, chrect.height);
        rect.set_color(m_style.text_color)
            .set_active_texture(FONT_TEXTURE_UNIT)
            .set_texcoords({ chrect.u1, chrect.v1 }, { chrect.u2, chrect.v2 })
            .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
        ui_context.add_rect(rect);
        xcurr += chrect.advance;
    }
}

float Label::get_min_width() const
{
    auto& ui_context = Context::get_instance();
    auto& font_metadata = ui_context.get_font().get_metadata();

    float xcurr = 0;
    for (char c : m_text) {
        auto chrect = get_rect_for_char(c, m_font_size);
        xcurr += chrect.advance;
    }

    return std::ceil(xcurr);
}

float Label::get_min_height() const
{
    auto& ui_context = Context::get_instance();
    auto& font_metadata = ui_context.get_font().get_metadata();

    float min_height = 0;
    float ycurr = m_font_size;
    for (char c : m_text) {
        auto chrect = get_rect_for_char(c, m_font_size);
        min_height = std::max(min_height, ycurr + chrect.y + chrect.height);
    }

    return std::ceil(min_height);
}

std::string Label::get_text() const
{
    return m_text;
}

void Label::set_text(const std::string& text)
{
    m_text = text;
}

int Label::get_font_size() const
{
    return m_font_size;
}

void Label::set_font_size(int size)
{
    m_font_size = size;
}

Label::CharRect Label::get_rect_for_char(char c, float font_size)
{
    auto& ui_context = Context::get_instance();
    auto& font_metadata = ui_context.get_font().get_metadata();

    const auto& info = font_metadata.info[c];
    float advance = info.xadvance * font_size / font_metadata.bitmap_pixel_height;

    float u1 = info.x / (float)font_metadata.bitmap_width;
    float v1 = 1 - info.y / (float)font_metadata.bitmap_height;
    float u2 = (info.x + info.width) / (float)font_metadata.bitmap_width;
    float v2 = 1 - (info.y + info.height) / (float)font_metadata.bitmap_height;

    float x = info.xoffset * font_size / font_metadata.bitmap_pixel_height;
    float y = info.yoffset * font_size / font_metadata.bitmap_pixel_height;
    float width = info.width * font_size / font_metadata.bitmap_pixel_height;
    float height = info.height * font_size / font_metadata.bitmap_pixel_height;

    return { x, y, width, height, u1, v1, u2, v2, advance };
}

}