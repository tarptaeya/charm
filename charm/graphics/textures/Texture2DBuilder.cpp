#include "Texture2DBuilder.h"
#include "stb_image.h"
#include <algorithm>
#include <iostream>

namespace charm {

Texture2DBuilder::Texture2DBuilder(const std::string& path)
    : m_path(path)
{
    stbi_set_flip_vertically_on_load(true);
}

Texture2DBuilder& Texture2DBuilder::set_texture_unit(GLenum texture_unit)
{
    m_texture_unit = texture_unit;
    return *this;
}

Texture2DBuilder& Texture2DBuilder::set_parameteri(GLenum name, GLint value)
{
    m_parameteri_map[name] = value;
    return *this;
}

Texture2D Texture2DBuilder::build()
{
    glGenTextures(1, &m_texture_id);
    glActiveTexture(m_texture_unit);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    for (auto entry : m_parameteri_map) {
        glTexParameteri(GL_TEXTURE_2D, entry.first, entry.second);
    }

    int width, height, channels;
    unsigned char* data = stbi_load(m_path.c_str(), &width, &height, &channels, 3);
    if (!data) {
        std::cerr << "[error] unable to read image: " << m_path << std::endl;
        std::cerr << stbi_failure_reason() << std::endl;
        std::exit(0);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    return Texture2D(m_texture_unit, m_texture_id);
}

}