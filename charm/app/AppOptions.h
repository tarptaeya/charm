#pragma once

#include <string>

namespace charm {

struct AppOptions {
    int window_width = 800;
    int window_height = 600;
    std::string window_title = "Charm Engine Demo";
};

}