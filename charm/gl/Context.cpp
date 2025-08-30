#include <glad/gl.h>

#include "Context.h"
#include <iostream>

namespace charm::gl {

const int Context::ARRAY_BUFFER = GL_ARRAY_BUFFER;
const int Context::ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER;
const int Context::FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
const int Context::VERTEX_SHADER = GL_VERTEX_SHADER;

Shader Context::create_shader(int type, const std::string& source) const
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

Program Context::create_program(const std::string& vertex_source, const std::string& fragment_source) const
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

void Context::use(const Program& program) const
{
    glUseProgram(program.get());
}

VertexArray Context::gen_vertex_array() const
{
    unsigned int vertex_array;
    glGenVertexArrays(1, &vertex_array);
    return VertexArray(vertex_array);
}

void Context::bind(const VertexArray& vertex_array) const
{
    glBindVertexArray(vertex_array.get());
}

void Context::enable_vertex_attrib_array(unsigned int index) const
{
    glEnableVertexAttribArray(index);
}

void Context::vertex_attrib_pointer(unsigned int index, int size, int type, bool normalized, int stride, const void* pointer) const
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void Context::vertex_attribi_pointer(unsigned int index, int size, int type, int stride, const void* pointer) const
{
    glVertexAttribIPointer(index, size, type, stride, pointer);
}

Buffer Context::gen_buffer() const
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    return Buffer(buffer);
}

void Context::bind(int type, const Buffer& buffer) const
{
    glBindBuffer(type, buffer.get());
}

void Context::buffer_data(int type, int size, const void* data, int usage)
{
    glBufferData(type, size, data, usage);
}

}