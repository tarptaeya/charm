#include <glad/gl.h>

#include "Context.h"
#include <iostream>

namespace charm::gl {

void Context::init(GLFWglproc (*fn)(const char*))
{
    gladLoadGL(fn);
}

void Context::disable(int capacity)
{
    glDisable(capacity);
}

void Context::enable(int capacity)
{
    glEnable(capacity);
}

void Context::viewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

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

int Context::get_uniform_location(Program& program, const std::string& name)
{
    if (!program.m_uniform_locations.count(name)) {
        program.m_uniform_locations[name] = glGetUniformLocation(program.get(), name.c_str());
    }

    return program.m_uniform_locations[name];
}

void Context::set_uniform(Program& program, const std::string& name, const Matrix4f& mat)
{
    int location = get_uniform_location(program, name);
    glUniformMatrix4fv(location, 1, false, mat.get_data());
}

void Context::set_uniform(Program& program, const std::string& name, int value)
{
    int location = get_uniform_location(program, name);
    glUniform1i(location, value);
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

void Context::unbind_vertex_array()
{
    glBindVertexArray(0);
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

void Context::bind(unsigned int type, const Buffer& buffer)
{
    glBindBuffer(type, buffer.get());
}

void Context::unbind_buffer(unsigned int type)
{
    glBindBuffer(type, 0);
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

Texture Context::gen_texture()
{
    unsigned int texture;
    glGenTextures(1, &texture);
    return Texture(texture);
}

void Context::active_texture(unsigned int unit)
{
    glActiveTexture(unit);
}

void Context::bind(unsigned int target, const Texture& texture)
{
    glBindTexture(target, texture.get());
}

void Context::unbind_texture(unsigned int target)
{
    glBindTexture(target, 0);
}

void Context::tex_parameteri(unsigned int target, unsigned int name, int param)
{
    glTexParameteri(target, name, param);
}

void Context::tex_image2d(unsigned int target, int level, int internal_format, int width, int height, int border, unsigned int format, unsigned int type, const void* data)
{
    glTexImage2D(target, level, internal_format, width, height, border, format, type, data);
}

void Context::generate_mipmap(unsigned int target)
{
    glGenerateMipmap(target);
}

Framebuffer Context::gen_framebuffer()
{
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    return Framebuffer(fbo);
}

void Context::bind(unsigned int target, const Framebuffer& framebuffer)
{
    glBindFramebuffer(target, framebuffer.get());
}

void Context::unbind_framebuffer(unsigned int target)
{
    glBindFramebuffer(target, 0);
}

void Context::blend_func(unsigned int sfactor, unsigned int dfactor)
{
    glBlendFunc(sfactor, dfactor);
}

}