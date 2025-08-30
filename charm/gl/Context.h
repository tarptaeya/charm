#pragma once

#include "Buffer.h"
#include "Program.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "defines.h"
#include "math/Matrix4f.h"
#include <string>

namespace charm::gl {

class Context {
public:
    Context() = default;

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    static void disable(int capability);
    static void enable(int capability);

    [[nodiscard]] static Shader create_shader(int type, const std::string& source);
    [[nodiscard]] static Program create_program(const std::string& vertex_source, const std::string& fragment_source);
    static void use(const Program& program);
    [[nodiscard]] static int get_uniform_location(Program& program, const std::string&);
    static void set_uniform(Program& program, const std::string&, const Matrix4f&);
    static void set_uniform(Program& program, const std::string&, int);

    [[nodiscard]] static VertexArray gen_vertex_array();
    static void bind(const VertexArray& vertex_array);
    static void enable_vertex_attrib_array(unsigned int index);
    static void vertex_attrib_pointer(unsigned int index, int size, int type, bool normalized, int stride, const void* pointer);
    static void vertex_attribi_pointer(unsigned int index, int size, int type, int stride, const void* pointer);

    [[nodiscard]] static Buffer gen_buffer();
    static void bind(int type, const Buffer& buffer);
    static void buffer_data(int type, int size, const void* data, int usage);
    static void buffer_sub_data(int target, int offset, int size, const void* data);

    static void draw_elements(int mode, int count, int type, const void* indices);

    [[nodiscard]] static Texture gen_texture();
    static void active_texture(unsigned int unit);
    static void bind(unsigned int target, const Texture& texture);
    static void tex_parameteri(unsigned int target, unsigned int name, int param);
    static void tex_image2d(unsigned int target, int level, int internal_format, int width, int height, int border, unsigned int format, unsigned int type, const void* data);
    static void tex_image2d(unsigned int target, const std::string& path);
    static void generate_mipmap(unsigned int target);
};

}