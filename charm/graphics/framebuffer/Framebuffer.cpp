#include "Framebuffer.h"
#include <glad/gl.h>

namespace charm {

Framebuffer::Framebuffer(unsigned int fbo, int width, int height, unsigned int color_texture, unsigned int depth_stencil_texture)
    : m_fbo(fbo)
    , m_width(width)
    , m_height(height)
    , m_color_texture(color_texture)
    , m_depth_stencil_texture(depth_stencil_texture)
{
}

Framebuffer::~Framebuffer()
{
    if (m_fbo != 0)
        glDeleteFramebuffers(1, &m_fbo);
    if (m_color_texture != 0)
        glDeleteTextures(1, &m_color_texture);
    if (m_depth_stencil_texture != 0)
        glDeleteTextures(1, &m_depth_stencil_texture);
}

Framebuffer::Framebuffer(Framebuffer&& other)
{
    m_fbo = other.m_fbo;
    m_width = other.m_width;
    m_height = other.m_height;
    m_color_texture = other.m_color_texture;
    m_depth_stencil_texture = other.m_depth_stencil_texture;

    other.m_fbo = other.m_width = other.m_height = other.m_color_texture = other.m_depth_stencil_texture = 0;
}

Framebuffer& Framebuffer::operator=(Framebuffer&& other)
{
    if (this == &other)
        return *this;

    if (m_fbo != 0)
        glDeleteFramebuffers(1, &m_fbo);
    if (m_color_texture != 0)
        glDeleteTextures(1, &m_color_texture);
    if (m_depth_stencil_texture != 0)
        glDeleteTextures(1, &m_depth_stencil_texture);

    m_fbo = other.m_fbo;
    m_width = other.m_width;
    m_height = other.m_height;
    m_color_texture = other.m_color_texture;
    m_depth_stencil_texture = other.m_depth_stencil_texture;

    other.m_fbo = other.m_width = other.m_height = other.m_color_texture = other.m_depth_stencil_texture = 0;
    return *this;
}

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_width, m_height);
}

unsigned int Framebuffer::get_color_texture() const
{
    return m_color_texture;
}

unsigned int Framebuffer::get_depth_stencil_texture() const
{
    return m_depth_stencil_texture;
}

}