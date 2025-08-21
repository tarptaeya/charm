#pragma once

namespace charm {

class Framebuffer {
    friend class FramebufferBuilder;

    int m_width = 0;
    int m_height = 0;
    unsigned int m_fbo = 0;
    unsigned int m_color_texture = 0;
    unsigned int m_depth_stencil_texture = 0;

    Framebuffer(unsigned int fbo, int width, int height, unsigned int color_texture, unsigned int depth_stencil_texture);

public:
    Framebuffer() = default;
    ~Framebuffer();

    Framebuffer(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    Framebuffer(Framebuffer&&);
    Framebuffer& operator=(Framebuffer&&);

    void bind();
    int get_width() const;
    int get_height() const;
    unsigned int get_gl_color_texture() const;
    unsigned int get_gl_depth_stencil_texture() const;
};

}