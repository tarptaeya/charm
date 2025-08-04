#include "XProgram.h"
#include <glad/gl.h>

XProgram::XProgram(unsigned int vertex_shader, unsigned int fragment_shader)
{
    m_program = glCreateProgram();
    glAttachShader(m_program, vertex_shader);
    glAttachShader(m_program, fragment_shader);
    glLinkProgram(m_program);
    int status;
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char log[512];
        glGetProgramInfoLog(m_program, sizeof(log), nullptr, log);
        glDeleteProgram(m_program);
        std::cerr << "[error] " << log << std::endl;
        std::exit(1);
    }
}

XProgram::~XProgram()
{
    if (m_program != 0)
        glDeleteProgram(m_program);
}

XProgram::XProgram(XProgram&& other)
{
    m_program = other.m_program;
    other.m_program = 0;
}

XProgram& XProgram::operator=(XProgram&& other)
{
    if (this == &other)
        return *this;

    if (m_program != 0)
        glDeleteProgram(m_program);

    m_program = other.m_program;
    other.m_program = 0;
    return *this;
}

void XProgram::use()
{
    glUseProgram(m_program);
}

void XProgram::set_uniform(const std::string& name, const XMatrix4f& mat)
{
    if (!m_uniform_locations.count(name)) {
        m_uniform_locations[name] = glGetUniformLocation(m_program, name.c_str());
    }

    int location = m_uniform_locations[name];
    glUniformMatrix4fv(location, 1, false, mat.get_data());
}

void XProgram::set_uniform(const std::string& name, int value)
{
    if (!m_uniform_locations.count(name)) {
        m_uniform_locations[name] = glGetUniformLocation(m_program, name.c_str());
    }

    int location = m_uniform_locations[name];
    glUniform1i(location, value);
}
