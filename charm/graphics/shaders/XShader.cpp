#include "XShader.h"
#include "io/XFileIO.h"
#include <iostream>

XShader::XShader(GLuint type, const std::string& source)
{
    m_shader = glCreateShader(type);
    const char* raw_source = source.c_str();
    glShaderSource(m_shader, 1, &raw_source, nullptr);
    glCompileShader(m_shader);
    int status;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char log[512];
        glGetShaderInfoLog(m_shader, sizeof(log), nullptr, log);
        glDeleteShader(m_shader);
        std::cerr << "[error] " << log << std::endl;
        std::exit(1);
    }
}

XShader::~XShader()
{
    if (m_shader != 0)
        glDeleteShader(m_shader);
}

XShader::XShader(XShader&& other)
{
    m_shader = other.m_shader;
    other.m_shader = 0;
}

XShader& XShader::operator=(XShader&& other)
{
    if (this == &other)
        return *this;

    m_shader = other.m_shader;
    other.m_shader = 0;
    return *this;
}