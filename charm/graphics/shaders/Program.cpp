#include "Program.h"
#include <glad/gl.h>

namespace charm {

Program::Program(const Shader& vertex, const Shader& fragment)
{
    m_program = glCreateProgram();
    glAttachShader(m_program, vertex.m_shader);
    glAttachShader(m_program, fragment.m_shader);
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

Program::~Program()
{
    if (m_program != 0)
        glDeleteProgram(m_program);
}

Program::Program(Program&& other)
{
    m_program = other.m_program;
    other.m_program = 0;
}

Program& Program::operator=(Program&& other)
{
    if (this == &other)
        return *this;

    if (m_program != 0)
        glDeleteProgram(m_program);

    m_program = other.m_program;
    other.m_program = 0;
    return *this;
}

void Program::use()
{
    glUseProgram(m_program);
}

void Program::set_uniform(const std::string& name, const Matrix4f& mat)
{
    if (!m_uniform_locations.count(name)) {
        m_uniform_locations[name] = glGetUniformLocation(m_program, name.c_str());
    }

    int location = m_uniform_locations[name];
    glUniformMatrix4fv(location, 1, false, mat.get_data());
}

void Program::set_uniform(const std::string& name, int value)
{
    if (!m_uniform_locations.count(name)) {
        m_uniform_locations[name] = glGetUniformLocation(m_program, name.c_str());
    }

    int location = m_uniform_locations[name];
    glUniform1i(location, value);
}

}