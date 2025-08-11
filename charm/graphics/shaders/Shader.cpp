#include "Shader.h"
#include "io/FileIO.h"
#include <iostream>

namespace charm {

Shader::Shader(GLuint type, const std::string& source)
{
    m_id = glCreateShader(type);
    const char* raw_source = source.c_str();
    glShaderSource(m_id, 1, &raw_source, nullptr);
    glCompileShader(m_id);
    int status;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char log[512];
        glGetShaderInfoLog(m_id, sizeof(log), nullptr, log);
        glDeleteShader(m_id);
        std::cerr << "[error] " << log << std::endl;
        std::exit(0);
    }
}

Shader::~Shader()
{
    if (m_id != 0)
        glDeleteShader(m_id);
}

Shader::Shader(Shader&& other)
{
    m_id = other.m_id;
    other.m_id = 0;
}

Shader& Shader::operator=(Shader&& other)
{
    if (this == &other)
        return *this;

    m_id = other.m_id;
    other.m_id = 0;
    return *this;
}

}