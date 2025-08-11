#include "Program.h"
#include <glad/gl.h>

namespace charm {

Program::Program(const Shader& vertex, const Shader& fragment)
{
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex.m_id);
    glAttachShader(m_id, fragment.m_id);
    glLinkProgram(m_id);
    int status;
    glGetProgramiv(m_id, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char log[512];
        glGetProgramInfoLog(m_id, sizeof(log), nullptr, log);
        glDeleteProgram(m_id);
        std::cerr << "[error] " << log << std::endl;
        std::exit(0);
    }
}

Program::~Program()
{
    if (m_id != 0)
        glDeleteProgram(m_id);
}

Program::Program(Program&& other)
{
    m_id = other.m_id;
    other.m_id = 0;
}

Program& Program::operator=(Program&& other)
{
    if (this == &other)
        return *this;

    if (m_id != 0)
        glDeleteProgram(m_id);

    m_id = other.m_id;
    other.m_id = 0;
    return *this;
}

void Program::use()
{
    glUseProgram(m_id);
}

void Program::set_uniform(const std::string& name, const Matrix4f& mat)
{
    if (!m_uniform_locations.count(name)) {
        m_uniform_locations[name] = glGetUniformLocation(m_id, name.c_str());
    }

    int location = m_uniform_locations[name];
    glUniformMatrix4fv(location, 1, false, mat.get_data());
}

void Program::set_uniform(const std::string& name, int value)
{
    if (!m_uniform_locations.count(name)) {
        m_uniform_locations[name] = glGetUniformLocation(m_id, name.c_str());
    }

    int location = m_uniform_locations[name];
    glUniform1i(location, value);
}

}