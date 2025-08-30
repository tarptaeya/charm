#include "TextureBuilder.h"
#include "stb_image.h"
#include <algorithm>
#include <iostream>

namespace charm {

TextureBuilder::TextureBuilder(const std::string& path)
    : m_path(path)
{
    stbi_set_flip_vertically_on_load(true);
}

TextureBuilder& TextureBuilder::set_texture_unit(unsigned int texture_unit)
{
    m_texture_unit = texture_unit;
    return *this;
}

TextureBuilder& TextureBuilder::set_parameteri(unsigned int name, int value)
{
    m_parameteri_map[name] = value;
    return *this;
}

gl::Texture TextureBuilder::build()
{
    gl::Texture texture = gl::Context::gen_texture();
    gl::Context::active_texture(m_texture_unit);
    gl::Context::bind(GL_TEXTURE_2D, texture);
    gl::Context::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl::Context::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl::Context::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gl::Context::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    for (auto entry : m_parameteri_map) {
        gl::Context::tex_parameteri(GL_TEXTURE_2D, entry.first, entry.second);
    }

    int width, height, channels;
    unsigned char* data = stbi_load(m_path.c_str(), &width, &height, &channels, 3);
    if (!data) {
        std::cerr << "[error] unable to read image: " << m_path << std::endl;
        std::cerr << stbi_failure_reason() << std::endl;
        std::exit(0);
    }

    gl::Context::tex_image2d(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    gl::Context::generate_mipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return texture;
}

}