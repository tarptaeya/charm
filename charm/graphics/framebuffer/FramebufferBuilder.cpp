#include "FramebufferBuilder.h"
#include <iostream>

namespace charm {

FramebufferBuilder& FramebufferBuilder::set_parameteri(GLenum name, GLint value)
{
    m_parameteri_map[name] = value;
    return *this;
}

Framebuffer FramebufferBuilder::create(int width, int height)
{
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    unsigned int color_texture;
    glGenTextures(1, &color_texture);
    glBindTexture(GL_TEXTURE_2D, color_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    for (const auto& entry : m_parameteri_map) {
        glTexParameteri(GL_TEXTURE_2D, entry.first, entry.second);
    }
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_texture, 0);

    unsigned int depth_stencil_texture;
    glGenTextures(1, &depth_stencil_texture);
    glBindTexture(GL_TEXTURE_2D, depth_stencil_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_stencil_texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "[error] framebuffer is not complete" << std::endl;
        std::exit(0);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return Framebuffer(fbo, width, height, color_texture, depth_stencil_texture);
}

}