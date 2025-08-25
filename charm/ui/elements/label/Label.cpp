#include "Label.h"

namespace charm::ui {

Label::Label(const std::string& text)
    : m_text(text)
{
    m_min_width = 0;
    m_min_height = m_font_size;
    m_expand_width = m_expand_height = false;
}

Label::~Label()
{
}

void Label::draw(ImmediateUI& api)
{
    float xcurr = m_x;
    float ycurr = m_y + m_font_size;

    std::string text = m_text;
    auto [is_overflow, overflow_index] = calculate_overflow_index(api);
    if (is_overflow) {
        text.resize(overflow_index);
        for (int i = 1; i <= 3 && overflow_index - i >= 0; ++i) {
            text[overflow_index - i] = '.';
        }
    }

    for (char c : text) {
        const auto& info = api.font_metadata.info[c];
        float advance = info.xadvance * m_font_size / api.font_metadata.bitmap_pixel_height;

        float u1 = info.x / (float)api.font_metadata.bitmap_width;
        float v1 = 1 - info.y / (float)api.font_metadata.bitmap_height;
        float u2 = (info.x + info.width) / (float)api.font_metadata.bitmap_width;
        float v2 = 1 - (info.y + info.height) / (float)api.font_metadata.bitmap_height;

        float x = xcurr + info.xoffset * m_font_size / api.font_metadata.bitmap_pixel_height;
        float y = ycurr + info.yoffset * m_font_size / api.font_metadata.bitmap_pixel_height;
        float width = info.width * m_font_size / api.font_metadata.bitmap_pixel_height;
        float height = info.height * m_font_size / api.font_metadata.bitmap_pixel_height;

        api.add_rect(x, y, width, height, { 1, 0, 0 }, 1, { u1, v1 }, { u2, v2 });
        xcurr += advance;
    }
}

std::pair<bool, int> Label::calculate_overflow_index(const ImmediateUI& api) const
{
    float xcurr = m_x;

    int index = -1;
    for (char c : m_text) {
        ++index;
        const auto& info = api.font_metadata.info[c];
        float x = xcurr + info.xoffset * m_font_size / api.font_metadata.bitmap_pixel_height;
        float width = info.width * m_font_size / api.font_metadata.bitmap_pixel_height;
        float advance = info.xadvance * m_font_size / api.font_metadata.bitmap_pixel_height;

        if (x + width > m_x + m_width) {
            return { true, index };
        }
        xcurr += advance;
    }

    return { false, index };
}

}