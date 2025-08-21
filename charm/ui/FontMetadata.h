#pragma once

#include <string>

namespace charm {

struct FontMetadata {
    struct CharInfo {
        int x, y, width, height;
        int xoffset, yoffset, xadvance;
    } info[128] = { 0 };

    int bitmap_width = 0;
    int bitmap_height = 0;
    int bitmap_pixel_height = 64;

    static FontMetadata parse(const std::string& path);
};

};