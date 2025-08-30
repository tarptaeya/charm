#pragma once

#include "gl/Context.h"
#include <string>
#include <unordered_map>

namespace charm {

class Texture2DBuilder {
    std::string m_path;
    unsigned int m_texture_id = 0;
    unsigned int m_texture_unit = GL_TEXTURE0;
    std::unordered_map<unsigned int, int> m_parameteri_map;

public:
    Texture2DBuilder(const std::string& path);
    Texture2DBuilder& set_texture_unit(unsigned int texture_unit);
    Texture2DBuilder& set_parameteri(unsigned int name, int value);
    gl::Texture build();
};

}