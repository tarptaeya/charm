#pragma once

#include <glad/gl.h>

namespace charm {

class Texture2D {
    unsigned int m_texture_id = 0;
    GLenum m_texture_unit = GL_TEXTURE0;

public:
    Texture2D() = default;
    Texture2D(GLenum m_texture_unit, unsigned int texture_id);
    ~Texture2D();

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    Texture2D(Texture2D&&);
    Texture2D& operator=(Texture2D&&);

    void bind();

    [[nodiscard]] unsigned int get_gl_texture() const;
    [[nodiscard]] GLenum get_texture_unit() const;
};

}