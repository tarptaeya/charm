#include "RenderTarget.h"
#include "misc/builder/FramebufferBuilder.h"

namespace charm {

RenderTarget::RenderTarget(int width, int height)
    : m_width(width)
    , m_height(height)
{
    auto data = FramebufferBuilder().create(width, height);
    m_framebuffer = std::move(std::get<0>(data));
    m_color_texture = std::move(std::get<1>(data));
    m_depth_stencil_texture = std::move(std::get<2>(data));
}

RenderTarget::~RenderTarget()
{
}

RenderTarget::RenderTarget(RenderTarget&& other)
{
    m_width = other.m_width;
    m_height = other.m_height;
    m_framebuffer = std::move(other.m_framebuffer);
    m_color_texture = std::move(other.m_color_texture);
    m_depth_stencil_texture = std::move(other.m_depth_stencil_texture);
    other.m_width = other.m_height = 0;
}

RenderTarget& RenderTarget::operator=(RenderTarget&& other)
{
    if (this == &other)
        return *this;

    m_width = other.m_width;
    m_height = other.m_height;
    m_framebuffer = std::move(other.m_framebuffer);
    m_color_texture = std::move(other.m_color_texture);
    m_depth_stencil_texture = std::move(other.m_depth_stencil_texture);
    other.m_width = other.m_height = 0;
    return *this;
}

int RenderTarget::get_width() const
{
    return m_width;
}

int RenderTarget::get_height() const
{
    return m_height;
}

gl::Framebuffer& RenderTarget::get_framebuffer()
{
    return m_framebuffer;
}

gl::Texture& RenderTarget::get_color_texture()
{
    return m_color_texture;
}

gl::Texture& RenderTarget::get_depth_stencil_texture()
{
    return m_depth_stencil_texture;
}

}