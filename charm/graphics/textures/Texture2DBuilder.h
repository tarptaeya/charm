#pragma once

#include "Texture2D.h"
#include <glad/gl.h>
#include <string>
#include <unordered_map>

namespace charm {

class Texture2DBuilder {
    std::string m_path;
    unsigned int m_texture_id = 0;
    GLenum m_texture_unit = GL_TEXTURE0;
    std::unordered_map<GLenum, GLint> m_parameteri_map;

public:
    Texture2DBuilder(const std::string& path);
    Texture2DBuilder& set_texture_unit(GLenum texture_unit);
    Texture2DBuilder& set_parameteri(GLenum name, GLint value);
    Texture2D build();
};

}