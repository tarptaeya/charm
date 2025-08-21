#include "Shader.h"
#include "io/FileIO.h"
#include <iostream>

namespace charm {

unsigned int create_gl_shader(GLenum type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* raw_source = source.c_str();
    glShaderSource(shader, 1, &raw_source, nullptr);
    glCompileShader(shader);
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char log[512];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        glDeleteShader(shader);
        std::cerr << "[error] " << log << std::endl;
        std::exit(0);
    }

    return shader;
}

Shader::Shader(GLuint program)
    : m_program(program)
{
}

Shader::Shader(const std::string& vertex_source, const std::string& fragment_source)
{
    unsigned int vertex_shader = create_gl_shader(GL_VERTEX_SHADER, vertex_source);
    unsigned int fragment_shader = create_gl_shader(GL_FRAGMENT_SHADER, fragment_source);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertex_shader);
    glAttachShader(m_program, fragment_shader);
    glLinkProgram(m_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    int status;
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char log[512];
        glGetProgramInfoLog(m_program, sizeof(log), nullptr, log);
        glDeleteProgram(m_program);
        std::cerr << "[error] " << log << std::endl;
        std::exit(0);
    }
}

Shader::~Shader()
{
    if (m_program != 0)
        glDeleteProgram(m_program);
}

Shader::Shader(Shader&& other)
{
    m_program = other.m_program;
    other.m_program = 0;
}

Shader& Shader::operator=(Shader&& other)
{
    if (this == &other)
        return *this;

    m_program = other.m_program;
    other.m_program = 0;
    return *this;
}

GLuint Shader::get_gl_program() const
{
    return m_program;
}

void Shader::use()
{
    glUseProgram(m_program);
}

void Shader::set_uniform(const std::string& name, const Matrix4f& mat)
{
    if (!m_uniform_locations.count(name)) {
        m_uniform_locations[name] = glGetUniformLocation(m_program, name.c_str());
    }

    int location = m_uniform_locations[name];
    glUniformMatrix4fv(location, 1, false, mat.get_data());
}

void Shader::set_uniform(const std::string& name, int value)
{
    if (!m_uniform_locations.count(name)) {
        m_uniform_locations[name] = glGetUniformLocation(m_program, name.c_str());
    }

    int location = m_uniform_locations[name];
    glUniform1i(location, value);
}

}