#include "UILabel.h"

namespace charm {

UILabel::UILabel(const std::string& text)
    : m_text(text)
{
}

UILabel::~UILabel()
{
}

void UILabel::draw(int _x, int _y, int _width, int _height, ImmediateUI& api)
{
    float bitmap_pixel_height = 64;
    float font_size = 30;

    api.ycursor += font_size;
    int xcurr = api.xcursor;
    int ycurr = api.ycursor;
    static bool debug = false;

    for (char c : m_text) {
        const auto& info = api.font_metadata.info[c];

        float u1 = info.x / (float)api.font_metadata.bitmap_width;
        float v1 = 1 - info.y / (float)api.font_metadata.bitmap_height;
        float u2 = (info.x + info.width) / (float)api.font_metadata.bitmap_width;
        float v2 = 1 - (info.y + info.height) / (float)api.font_metadata.bitmap_height;

        float x = xcurr + info.xoffset * font_size / api.font_metadata.bitmap_pixel_height;
        float y = ycurr + info.yoffset * font_size / api.font_metadata.bitmap_pixel_height;
        float width = info.width * font_size / api.font_metadata.bitmap_pixel_height;
        float height = info.height * font_size / api.font_metadata.bitmap_pixel_height;
        api.add_rect(x, y, width, height, { 1, 0, 0 }, 1, { u1, v1 }, { u2, v2 });
        xcurr += info.xadvance * font_size / api.font_metadata.bitmap_pixel_height;
    }
}

}