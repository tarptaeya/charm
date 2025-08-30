#include <glad/gl.h>

#include "Context.h"
#include <iostream>

namespace charm::gl {

const int Context::ARRAY_BUFFER = GL_ARRAY_BUFFER;
const int Context::DYNAMIC_DRAW = GL_DYNAMIC_DRAW;
const int Context::ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER;
const int Context::FLOAT = GL_FLOAT;
const int Context::FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
const int Context::INT = GL_INT;
const int Context::TRIANGLES = GL_TRIANGLES;
const int Context::UNSIGNED_INT = GL_UNSIGNED_INT;
const int Context::VERTEX_SHADER = GL_VERTEX_SHADER;

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

void Context::use(const Program& program)
{
    glUseProgram(program.get());
}

VertexArray Context::gen_vertex_array()
{
    unsigned int vertex_array;
    glGenVertexArrays(1, &vertex_array);
    return VertexArray(vertex_array);
}

void Context::bind(const VertexArray& vertex_array)
{
    glBindVertexArray(vertex_array.get());
}

void Context::enable_vertex_attrib_array(unsigned int index)
{
    glEnableVertexAttribArray(index);
}

void Context::vertex_attrib_pointer(unsigned int index, int size, int type, bool normalized, int stride, const void* pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void Context::vertex_attribi_pointer(unsigned int index, int size, int type, int stride, const void* pointer)
{
    glVertexAttribIPointer(index, size, type, stride, pointer);
}

Buffer Context::gen_buffer()
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    return Buffer(buffer);
}

void Context::bind(int type, const Buffer& buffer)
{
    glBindBuffer(type, buffer.get());
}

void Context::buffer_data(int type, int size, const void* data, int usage)
{
    glBufferData(type, size, data, usage);
}

void Context::buffer_sub_data(int target, int offset, int size, const void* data)
{
    glBufferSubData(target, offset, size, data);
}

void Context::draw_elements(int mode, int count, int type, const void* indices)
{
    glDrawElements(mode, count, type, indices);
}

}