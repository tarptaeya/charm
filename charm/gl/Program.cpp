#include "Program.h"
#include <glad/gl.h>

namespace charm::gl {

Program::Program(unsigned int handle)
    : m_handle(handle)
{
}

Program::~Program()
{
    if (m_handle != 0)
        glDeleteProgram(m_handle);

    m_handle = 0;
}

Program::Program(Program&& other)
{
    m_handle = other.m_handle;
    other.m_handle = 0;
}

Program& Program::operator=(Program&& other)
{
    if (this == &other)
        return *this;

    if (m_handle != 0)
        glDeleteProgram(m_handle);

    m_handle = other.m_handle;
    other.m_handle = 0;
    return *this;
}

unsigned int Program::get() const
{
    return m_handle;
}

}