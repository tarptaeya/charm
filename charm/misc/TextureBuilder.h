#pragma once

#include "gl/Context.h"
#include <string>
#include <unordered_map>

namespace charm {

class TextureBuilder {
    std::string m_path;
    unsigned int m_texture_id = 0;
    unsigned int m_active_texture = GL_TEXTURE0;
    unsigned int m_internal_format = GL_RGB;
    unsigned int m_format = GL_RGB;
    unsigned int m_type = GL_UNSIGNED_BYTE;
    std::unordered_map<unsigned int, int> m_parameteri_map;

public:
    TextureBuilder(const std::string& path);
    TextureBuilder& set_active_texture(unsigned int texture_unit);
    TextureBuilder& set_internal_format(unsigned int internal_format);
    TextureBuilder& set_format(unsigned int format);
    TextureBuilder& set_type(unsigned int type);
    TextureBuilder& set_parameteri(unsigned int name, int value);
    gl::Texture build();
};

}