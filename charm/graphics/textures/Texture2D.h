#pragma once

#include "ImageData.h"
#include <glad/gl.h>

namespace charm {

class Texture2D {
    unsigned int m_texture_id = 0;
    GLenum m_texture_unit = GL_TEXTURE0;

    Texture2D(GLenum m_texture_unit, unsigned int texture_id);

    friend class Texture2DBuilder;

public:
    Texture2D() = default;
    ~Texture2D();

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    Texture2D(Texture2D&&);
    Texture2D& operator=(Texture2D&&);

    void bind();
};

}