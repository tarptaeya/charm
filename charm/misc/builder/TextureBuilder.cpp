#include "TextureBuilder.h"
#include "misc/stb_image.h"
#include <algorithm>
#include <iostream>

namespace charm {

TextureBuilder::TextureBuilder(const std::string& path)
    : m_path(path)
{
    stbi_set_flip_vertically_on_load(true);
}

TextureBuilder& TextureBuilder::set_active_texture(unsigned int texture_unit)
{
    m_active_texture = texture_unit;
    return *this;
}

TextureBuilder& TextureBuilder::set_internal_format(unsigned int internal_format)
{
    m_internal_format = internal_format;
    return *this;
}

TextureBuilder& TextureBuilder::set_format(unsigned int format)
{
    m_format = format;
    return *this;
}

TextureBuilder& TextureBuilder::set_type(unsigned int type)
{
    m_type = type;
    return *this;
}

TextureBuilder& TextureBuilder::set_parameteri(unsigned int name, int value)
{
    m_parameteri_map[name] = value;
    return *this;
}

gl::Texture TextureBuilder::build()
{
    gl::Texture texture = gl::gen_texture();
    gl::active_texture(m_active_texture);
    gl::bind(GL_TEXTURE_2D, texture);
    gl::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gl::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    for (auto entry : m_parameteri_map) {
        gl::tex_parameteri(GL_TEXTURE_2D, entry.first, entry.second);
    }

    int width, height, channels;
    unsigned char* data = stbi_load(m_path.c_str(), &width, &height, &channels, 3);
    if (!data) {
        std::cerr << "[error] unable to read image: " << m_path << std::endl;
        std::cerr << stbi_failure_reason() << std::endl;
        std::exit(0);
    }

    gl::tex_image2d(GL_TEXTURE_2D, 0, m_internal_format, width, height, 0, m_format, m_type, data);
    gl::generate_mipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return texture;
}

}