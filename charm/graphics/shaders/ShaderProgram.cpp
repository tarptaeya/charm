#include "ShaderProgram.h"
#include <glad/gl.h>

namespace charm {

ShaderProgram::ShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader)
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

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_program);
}

void ShaderProgram::use()
{
    glUseProgram(m_program);
}

}