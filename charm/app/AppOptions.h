#pragma once

#include <string>

namespace charm {

struct AppOptions {
    int window_width = 800;
    int window_height = 600;
    std::string window_title = "Charm Engine Demo";
    std::string font_texture_path = "res/demo/bitmap.png";
    std::string font_metadata_path = "res/demo/font.txt";
};

}