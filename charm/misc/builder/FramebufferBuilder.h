#pragma once

#include "gl/Context.h"
#include <unordered_map>

namespace charm {

class FramebufferBuilder {
    std::unordered_map<unsigned int, int> m_parameteri_map;

public:
    FramebufferBuilder& set_parameteri(unsigned int name, int value);
    std::tuple<gl::Framebuffer, gl::Texture, gl::Texture> create(int width, int height);
};

}