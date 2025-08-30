#include "VertexArray.h"
#include <glad/gl.h>

namespace charm::gl {

VertexArray::VertexArray(unsigned int handle)
    : m_handle(handle)
{
}

VertexArray::~VertexArray()
{
    if (m_handle != 0)
        glDeleteVertexArrays(1, &m_handle);

    m_handle = 0;
}

VertexArray::VertexArray(VertexArray&& other)
{
    m_handle = other.m_handle;
    other.m_handle = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other)
{
    if (this == &other)
        return *this;

    if (m_handle != 0)
        glDeleteVertexArrays(1, &m_handle);

    m_handle = other.m_handle;
    other.m_handle = 0;
    return *this;
}

unsigned int VertexArray::get() const
{
    return m_handle;
}

}