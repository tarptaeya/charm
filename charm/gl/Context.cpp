#include <glad/gl.h>

#include "Context.h"
#include <iostream>

namespace charm::gl {

void init(GLFWglproc (*fn)(const char*))
{
    gladLoadGL(fn);
}

void disable(int capacity)
{
    glDisable(capacity);
}

void enable(int capacity)
{
    glEnable(capacity);
}

void depth_mask(bool flag)
{
    glDepthMask(flag);
}

void viewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void clear_color(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void clear(unsigned int mask)
{
    glClear(mask);
}

Shader create_shader(int type, const std::string& source)
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

Program create_program(const std::string& vertex_source, const std::string& fragment_source)
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

void use(const Program& program)
{
    glUseProgram(program.get());
}

int get_uniform_location(Program& program, const std::string& name)
{
    if (!program.uniform_locations.count(name)) {
        program.uniform_locations[name] = glGetUniformLocation(program.get(), name.c_str());
    }

    return program.uniform_locations[name];
}

void set_uniform(Program& program, const std::string& name, const Mat4& mat)
{
    int location = get_uniform_location(program, name);
    glUniformMatrix4fv(location, 1, false, mat.get_data());
}

void set_uniform(Program& program, const std::string& name, int value)
{
    int location = get_uniform_location(program, name);
    glUniform1i(location, value);
}

VertexArray gen_vertex_array()
{
    unsigned int vertex_array;
    glGenVertexArrays(1, &vertex_array);
    return VertexArray(vertex_array);
}

void bind(const VertexArray& vertex_array)
{
    glBindVertexArray(vertex_array.get());
}

void reset_vertex_array()
{
    glBindVertexArray(0);
}

void enable_vertex_attrib_array(unsigned int index)
{
    glEnableVertexAttribArray(index);
}

void vertex_attrib_pointer(unsigned int index, int size, int type, bool normalized, int stride, const void* pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void vertex_attribi_pointer(unsigned int index, int size, int type, int stride, const void* pointer)
{
    glVertexAttribIPointer(index, size, type, stride, pointer);
}

Buffer gen_buffer()
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    return Buffer(buffer);
}

void bind(unsigned int type, const Buffer& buffer)
{
    glBindBuffer(type, buffer.get());
}

void reset_buffer(unsigned int type)
{
    glBindBuffer(type, 0);
}

void buffer_data(int type, int size, const void* data, int usage)
{
    glBufferData(type, size, data, usage);
}

void buffer_sub_data(int target, int offset, int size, const void* data)
{
    glBufferSubData(target, offset, size, data);
}

void draw_elements(int mode, int count, int type, const void* indices)
{
    glDrawElements(mode, count, type, indices);
}

Texture gen_texture()
{
    unsigned int texture;
    glGenTextures(1, &texture);
    return Texture(texture);
}

void active_texture(unsigned int unit)
{
    glActiveTexture(unit);
}

void bind(unsigned int target, const Texture& texture)
{
    glBindTexture(target, texture.get());
}

void reset_texture(unsigned int target)
{
    glBindTexture(target, 0);
}

void tex_parameteri(unsigned int target, unsigned int name, int param)
{
    glTexParameteri(target, name, param);
}

void tex_image2d(unsigned int target, int level, int internal_format, int width, int height, int border, unsigned int format, unsigned int type, const void* data)
{
    glTexImage2D(target, level, internal_format, width, height, border, format, type, data);
}

void generate_mipmap(unsigned int target)
{
    glGenerateMipmap(target);
}

Framebuffer gen_framebuffer()
{
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    return Framebuffer(fbo);
}

void bind(unsigned int target, const Framebuffer& framebuffer)
{
    glBindFramebuffer(target, framebuffer.get());
}

void reset_framebuffer(unsigned int target)
{
    glBindFramebuffer(target, 0);
}

bool check_framebuffer_status(unsigned int target)
{
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void framebuffer_texture2d(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level)
{
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void blend_func(unsigned int sfactor, unsigned int dfactor)
{
    glBlendFunc(sfactor, dfactor);
}

}