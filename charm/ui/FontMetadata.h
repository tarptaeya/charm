#pragma once

namespace charm {

struct FontMetadata {
    struct CharInfo {
        int x0, y0, x1, y1;
        int xoffset, yoffset, xadvance;
    } info[128] = { 0 };
};

};