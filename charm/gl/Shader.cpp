#include "Shader.h"
#include <glad/gl.h>

namespace charm::gl {

Shader::Shader(unsigned int handle)
    : m_handle(handle)
{
}

Shader::~Shader()
{
    if (m_handle != 0)
        glDeleteShader(m_handle);

    m_handle = 0;
}

unsigned int Shader::get() const
{
    return m_handle;
}

}