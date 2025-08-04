#include "XTexture2D.h"

XTexture2D::XTexture2D(GLenum texture_unit, unsigned int texture_id)
    : m_texture_unit(texture_unit)
    , m_texture_id(texture_id)
{
}

XTexture2D::~XTexture2D()
{
    if (m_texture_id != 0)
        glDeleteTextures(1, &m_texture_id);
}

XTexture2D::XTexture2D(XTexture2D&& other)
{
    if (m_texture_id != 0)
        glDeleteTextures(1, &m_texture_id);

    m_texture_id = other.m_texture_id;
    m_texture_unit = other.m_texture_unit;
    other.m_texture_id = 0;
}

XTexture2D& XTexture2D::operator=(XTexture2D&& other)
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

void XTexture2D::bind()
{
    glActiveTexture(m_texture_unit);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}
