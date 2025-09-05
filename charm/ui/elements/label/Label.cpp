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
        const auto& info = font_metadata.info[c];
        float advance = info.xadvance * m_font_size / font_metadata.bitmap_pixel_height;

        float u1 = info.x / (float)font_metadata.bitmap_width;
        float v1 = 1 - info.y / (float)font_metadata.bitmap_height;
        float u2 = (info.x + info.width) / (float)font_metadata.bitmap_width;
        float v2 = 1 - (info.y + info.height) / (float)font_metadata.bitmap_height;

        float x = xcurr + info.xoffset * m_font_size / font_metadata.bitmap_pixel_height;
        float y = ycurr + info.yoffset * m_font_size / font_metadata.bitmap_pixel_height;
        float width = info.width * m_font_size / font_metadata.bitmap_pixel_height;
        float height = info.height * m_font_size / font_metadata.bitmap_pixel_height;

        Context::Rect rect(x, y, width, height);
        rect.set_color({ 0, 0, 0 })
            .set_active_texture(FONT_TEXTURE_UNIT)
            .set_texcoords({ u1, v1 }, { u2, v2 });
        ui_context.add_rect(rect);
        xcurr += advance;
    }
}

float Label::get_min_width() const
{
    auto& ui_context = Context::get_instance();
    auto& font_metadata = ui_context.get_font().get_metadata();

    float xcurr = 0;
    for (char c : m_text) {
        const auto& info = font_metadata.info[c];
        float x = xcurr + info.xoffset * m_font_size / font_metadata.bitmap_pixel_height;
        float width = info.width * m_font_size / font_metadata.bitmap_pixel_height;
        float advance = info.xadvance * m_font_size / font_metadata.bitmap_pixel_height;

        xcurr += advance;
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
        const auto& info = font_metadata.info[c];
        float y = ycurr + info.yoffset * m_font_size / font_metadata.bitmap_pixel_height;
        float height = info.height * m_font_size / font_metadata.bitmap_pixel_height;
        min_height = std::max(min_height, y + height);
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

void Label::set_font_size(int size)
{
    m_font_size = size;
}

}