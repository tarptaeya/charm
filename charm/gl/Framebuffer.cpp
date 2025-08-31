#include "Framebuffer.h"
#include <glad/gl.h>

namespace charm::gl {

Framebuffer::Framebuffer(unsigned int handle)
    : m_handle(handle)
{
}

Framebuffer::~Framebuffer()
{
    if (m_handle != 0)
        glDeleteFramebuffers(1, &m_handle);

    m_handle = 0;
}

Framebuffer::Framebuffer(Framebuffer&& other)
{
    m_handle = other.m_handle;
    other.m_handle = 0;
}

Framebuffer& Framebuffer::operator=(Framebuffer&& other)
{
    if (this == &other)
        return *this;

    if (m_handle != 0)
        glDeleteFramebuffers(1, &m_handle);

    m_handle = other.m_handle;
    other.m_handle = 0;
    return *this;
}

unsigned int Framebuffer::get() const
{
    return m_handle;
}

}