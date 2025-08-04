#pragma once

#include "XImageData.h"
#include <glad/gl.h>

class XTexture2D {
    unsigned int m_texture_id = 0;
    GLenum m_texture_unit = GL_TEXTURE0;

    XTexture2D(GLenum m_texture_unit, unsigned int texture_id);

    friend class XTexture2DBuilder;

public:
    XTexture2D() = default;
    ~XTexture2D();

    XTexture2D(const XTexture2D&) = delete;
    XTexture2D& operator=(const XTexture2D&) = delete;

    XTexture2D(XTexture2D&&);
    XTexture2D& operator=(XTexture2D&&);

    void bind();
};
