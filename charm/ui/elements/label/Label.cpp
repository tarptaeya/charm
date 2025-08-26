#include "Label.h"

namespace charm::ui {

Label::Label(ImmediateUI& context, const std::string& text)
    : Element(context)
    , m_text(text)
{
}

Label::~Label()
{
}

void Label::draw()
{
    float xcurr = m_x;
    float ycurr = m_y + m_font_size;

    std::string text = m_text;
    auto [is_overflow, overflow_index] = calculate_overflow_index();
    if (is_overflow) {
        text.resize(overflow_index);
        for (int i = 1; i <= 3 && overflow_index - i >= 0; ++i) {
            text[overflow_index - i] = '.';
        }
    }

    for (char c : text) {
        const auto& info = m_context.font_metadata.info[c];
        float advance = info.xadvance * m_font_size / m_context.font_metadata.bitmap_pixel_height;

        float u1 = info.x / (float)m_context.font_metadata.bitmap_width;
        float v1 = 1 - info.y / (float)m_context.font_metadata.bitmap_height;
        float u2 = (info.x + info.width) / (float)m_context.font_metadata.bitmap_width;
        float v2 = 1 - (info.y + info.height) / (float)m_context.font_metadata.bitmap_height;

        float x = xcurr + info.xoffset * m_font_size / m_context.font_metadata.bitmap_pixel_height;
        float y = ycurr + info.yoffset * m_font_size / m_context.font_metadata.bitmap_pixel_height;
        float width = info.width * m_font_size / m_context.font_metadata.bitmap_pixel_height;
        float height = info.height * m_font_size / m_context.font_metadata.bitmap_pixel_height;

        m_context.add_rect(x, y, width, height, { 1, 0, 0 }, 1, { u1, v1 }, { u2, v2 });
        xcurr += advance;
    }
}

float Label::get_min_width() const
{
    float xcurr = 0;
    for (char c : m_text) {
        const auto& info = m_context.font_metadata.info[c];
        float x = xcurr + info.xoffset * m_font_size / m_context.font_metadata.bitmap_pixel_height;
        float width = info.width * m_font_size / m_context.font_metadata.bitmap_pixel_height;
        float advance = info.xadvance * m_font_size / m_context.font_metadata.bitmap_pixel_height;

        xcurr += advance;
    }

    return xcurr;
}

float Label::get_min_height() const
{
    return m_font_size;
}

std::string Label::get_text() const
{
    return m_text;
}

void Label::set_text(const std::string& text)
{
    m_text = text;
}

std::pair<bool, int> Label::calculate_overflow_index() const
{
    float xcurr = m_x;

    int index = -1;
    for (char c : m_text) {
        ++index;
        const auto& info = m_context.font_metadata.info[c];
        float x = xcurr + info.xoffset * m_font_size / m_context.font_metadata.bitmap_pixel_height;
        float width = info.width * m_font_size / m_context.font_metadata.bitmap_pixel_height;
        float advance = info.xadvance * m_font_size / m_context.font_metadata.bitmap_pixel_height;

        if (x + width > m_x + m_width) {
            return { true, index };
        }
        xcurr += advance;
    }

    return { false, index };
}

}