#include "Texture2DBuilder.h"
#include "io/ppm/PPMReader.h"
#include <algorithm>
#include <iostream>

namespace charm {

static ImageData read_path(const std::string& path)
{
    int n = path.length();
    std::string extension;
    for (int i = n - 1; i >= 0; --i) {
        extension += path[i];
        if (path[i] == '.')
            break;
    }
    std::reverse(extension.begin(), extension.end());

    if (extension == ".ppm") {
        return PPMReader::read(path);
    } else {
        std::cerr << "[error] image format not supported: " << extension << std::endl;
        std::exit(0);
    }
}

Texture2DBuilder::Texture2DBuilder(const std::string& path)
    : m_path(path)
{
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
    ImageData image_data = read_path(m_path);

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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_data.get_width(), image_data.get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, &image_data.get_data()[0]);
    glGenerateMipmap(GL_TEXTURE_2D);

    return Texture2D(m_texture_unit, m_texture_id);
}

}