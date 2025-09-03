#pragma once

#include "gl/Context.h"

namespace charm {

class RenderTarget {
    int m_width = 0;
    int m_height = 0;
    gl::Framebuffer m_framebuffer;
    gl::Texture m_color_texture;
    gl::Texture m_depth_stencil_texture;

public:
    RenderTarget() = default;
    RenderTarget(int width, int height);
    ~RenderTarget();

    RenderTarget(const RenderTarget&) = delete;
    RenderTarget& operator=(const RenderTarget&) = delete;

    RenderTarget(RenderTarget&&);
    RenderTarget& operator=(RenderTarget&&);

    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;

    [[nodiscard]] gl::Framebuffer& get_framebuffer();
    [[nodiscard]] gl::Texture& get_color_texture();
    [[nodiscard]] gl::Texture& get_depth_stencil_texture();
};

}