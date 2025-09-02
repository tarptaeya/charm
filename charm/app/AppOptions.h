#pragma once

#include <iostream>
#include <string>

namespace charm {

struct AppOptions {
    int window_width = 800;
    int window_height = 600;
    std::string window_title = "Charm Engine Demo";
    std::string font_texture_path;
    std::string font_metadata_path;
    std::string ui_vertex_shader_path = "res/charm/ui.vertex.glsl";
    std::string ui_fragment_shader_path = "res/charm/ui.fragment.glsl";

    bool validate() const
    {
        if (font_texture_path.length() == 0 || font_metadata_path.length() == 0) {
            std::cout << "[error] please set font texture and metadata path in app options" << std::endl;
            return false;
        }

        if (ui_vertex_shader_path.length() == 0 || ui_fragment_shader_path.length() == 0) {
            std::cout << "[error] please set ui vertex and fragment shader path in app options" << std::endl;
            return false;
        }

        return true;
    }
};

}