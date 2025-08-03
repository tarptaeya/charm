#include "Texture2D.h"

namespace charm {

Texture2D::Texture2D(GLenum texture_unit, unsigned int texture_id)
    : m_texture_unit(texture_unit)
    , m_texture_id(texture_id)
{
}

Texture2D::~Texture2D()
{
    if (m_texture_id != 0)
        glDeleteTextures(1, &m_texture_id);
}

Texture2D::Texture2D(Texture2D&& other)
{
    if (m_texture_id != 0)
        glDeleteTextures(1, &m_texture_id);

    m_texture_id = other.m_texture_id;
    m_texture_unit = other.m_texture_unit;
    other.m_texture_id = 0;
}

Texture2D& Texture2D::operator=(Texture2D&& other)
{
    if (this == &other)
        return *this;

    if (m_texture_id != 0)
        glDeleteTextures(1, &m_texture_id);

    m_texture_id = other.m_texture_id;
    m_texture_unit = other.m_texture_unit;
    other.m_texture_id = 0;
    return *this;
}

void Texture2D::bind()
{
    glActiveTexture(m_texture_unit);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

}