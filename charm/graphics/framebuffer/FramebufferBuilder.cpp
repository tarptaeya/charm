#include "FramebufferBuilder.h"
#include <iostream>

namespace charm {

FramebufferBuilder& FramebufferBuilder::set_parameteri(unsigned int name, int value)
{
    m_parameteri_map[name] = value;
    return *this;
}

std::tuple<gl::Framebuffer, gl::Texture, gl::Texture> FramebufferBuilder::create(int width, int height)
{
    gl::Framebuffer framebuffer = gl::Context::gen_framebuffer();
    gl::Context::bind(GL_FRAMEBUFFER, framebuffer);

    gl::Context::active_texture(GL_TEXTURE0);
    gl::Texture color_texture = gl::Context::gen_texture();
    gl::Context::bind(GL_TEXTURE_2D, color_texture);
    gl::Context::tex_image2d(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    gl::Context::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl::Context::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl::Context::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl::Context::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    for (const auto& entry : m_parameteri_map) {
        gl::Context::tex_parameteri(GL_TEXTURE_2D, entry.first, entry.second);
    }
    gl::Context::framebuffer_texture2d(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_texture.get(), 0);

    gl::Context::active_texture(GL_TEXTURE0);
    gl::Texture depth_stencil_texture = gl::Context::gen_texture();
    gl::Context::bind(GL_TEXTURE_2D, depth_stencil_texture);
    gl::Context::tex_image2d(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    gl::Context::framebuffer_texture2d(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_stencil_texture.get(), 0);

    if (!gl::Context::check_framebuffer_status(GL_FRAMEBUFFER)) {
        std::cerr << "[error] framebuffer is not complete" << std::endl;
        std::exit(0);
    }

    gl::Context::unbind_framebuffer(GL_FRAMEBUFFER);
    return { std::move(framebuffer), std::move(color_texture), std::move(depth_stencil_texture) };
}

}