#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Buffer.h"
#include "Framebuffer.h"
#include "Program.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "constants.h"
#include "math/Mat4.h"
#include <string>

namespace charm {

class Application;

}

namespace charm::gl {

class Context {
    friend class charm::Application;

    static void init(GLFWglproc (*fn)(const char*));

public:
    Context() = default;

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    static void disable(int capability);
    static void enable(int capability);

    static void viewport(int x, int y, int width, int height);

    static void clear_color(float r, float g, float b, float a);
    static void clear(unsigned int mask);

    [[nodiscard]] static Shader create_shader(int type, const std::string& source);
    [[nodiscard]] static Program create_program(const std::string& vertex_source, const std::string& fragment_source);
    static void use(const Program& program);
    [[nodiscard]] static int get_uniform_location(Program& program, const std::string&);
    static void set_uniform(Program& program, const std::string&, const Mat4&);
    static void set_uniform(Program& program, const std::string&, int);

    [[nodiscard]] static VertexArray gen_vertex_array();
    static void bind(const VertexArray& vertex_array);
    static void reset_vertex_array();
    static void enable_vertex_attrib_array(unsigned int index);
    static void vertex_attrib_pointer(unsigned int index, int size, int type, bool normalized, int stride, const void* pointer);
    static void vertex_attribi_pointer(unsigned int index, int size, int type, int stride, const void* pointer);

    [[nodiscard]] static Buffer gen_buffer();
    static void bind(unsigned int type, const Buffer& buffer);
    static void reset_buffer(unsigned int type);
    static void buffer_data(int type, int size, const void* data, int usage);
    static void buffer_sub_data(int target, int offset, int size, const void* data);

    static void draw_elements(int mode, int count, int type, const void* indices);

    [[nodiscard]] static Texture gen_texture();
    static void active_texture(unsigned int unit);
    static void bind(unsigned int target, const Texture& texture);
    static void reset_texture(unsigned int target);
    static void tex_parameteri(unsigned int target, unsigned int name, int param);
    static void tex_image2d(unsigned int target, int level, int internal_format, int width, int height, int border, unsigned int format, unsigned int type, const void* data);
    static void generate_mipmap(unsigned int target);

    [[nodiscard]] static Framebuffer gen_framebuffer();
    static void bind(unsigned int target, const Framebuffer& framebuffer);
    static void reset_framebuffer(unsigned int target);
    [[nodiscard]] static bool check_framebuffer_status(unsigned int target);
    static void framebuffer_texture2d(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level);

    static void blend_func(unsigned int sfactor, unsigned int dfactor);
};

}