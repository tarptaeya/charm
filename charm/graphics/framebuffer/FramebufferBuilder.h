#pragma once

#include "Framebuffer.h"
#include <glad/gl.h>
#include <unordered_map>

namespace charm {

class FramebufferBuilder {
    std::unordered_map<GLenum, GLint> m_parameteri_map;

public:
    FramebufferBuilder& set_parameteri(GLenum name, GLint value);
    Framebuffer create(int width, int height);
};

}