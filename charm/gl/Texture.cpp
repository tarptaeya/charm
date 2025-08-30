#include "Texture.h"
#include <glad/gl.h>

namespace charm::gl {

Texture::Texture(unsigned int handle)
    : m_handle(handle)
{
}

Texture::~Texture()
{
    if (m_handle != 0)
        glDeleteTextures(1, &m_handle);

    m_handle = 0;
}

Texture::Texture(Texture&& other)
{
    m_handle = other.m_handle;
    other.m_handle = 0;
}

Texture& Texture::operator=(Texture&& other)
{
    if (this == &other)
        return *this;

    if (m_handle != 0)
        glDeleteTextures(1, &m_handle);

    m_handle = other.m_handle;
    other.m_handle = 0;
	return *this;
}

unsigned int Texture::get() const
{
    return m_handle;
}

}