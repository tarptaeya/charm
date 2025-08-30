#include "Buffer.h"
#include <glad/gl.h>

namespace charm::gl {

Buffer::Buffer(unsigned int handle)
    : m_handle(handle)
{
}

Buffer::~Buffer()
{
    if (m_handle != 0)
        glDeleteBuffers(1, &m_handle);

    m_handle = 0;
}

unsigned int Buffer::get() const
{
    return m_handle;
}

}