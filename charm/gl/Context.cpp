#include <glad/gl.h>

#include "Context.h"
#include <iostream>

namespace charm::gl {

const int Context::VERTEX_SHADER = GL_VERTEX_SHADER;
const int Context::FRAGMENT_SHADER = GL_FRAGMENT_SHADER;

Shader Context::create_shader(int type, const std::string& source)
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

    return Shader(shader);
}

Program Context::create_program(const std::string& vertex_source, const std::string& fragment_source)
{
    Shader vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source);
    Shader fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex_shader.get());
    glAttachShader(program, fragment_shader.get());
    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char log[512];
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        glDeleteProgram(program);
        std::cerr << "[error] " << log << std::endl;
        std::exit(0);
    }

    return Program(program);
}

}