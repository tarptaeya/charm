#pragma once

#include "Buffer.h"
#include "Program.h"
#include "Shader.h"
#include "VertexArray.h"
#include <string>

namespace charm::gl {

class Context {
public:
    Context() = default;

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    static Shader create_shader(int type, const std::string& source);
    static Program create_program(const std::string& vertex_source, const std::string& fragment_source);
    static void use(const Program& program);

    static VertexArray gen_vertex_array();
    static void bind(const VertexArray& vertex_array);
    static void enable_vertex_attrib_array(unsigned int index);
    static void vertex_attrib_pointer(unsigned int index, int size, int type, bool normalized, int stride, const void* pointer);
    static void vertex_attribi_pointer(unsigned int index, int size, int type, int stride, const void* pointer);

    static Buffer gen_buffer();
    static void bind(int type, const Buffer& buffer);
    static void buffer_data(int type, int size, const void* data, int usage);
    static void buffer_sub_data(int target, int offset, int size, const void* data);

    static void draw_elements(int mode, int count, int type, const void* indices);

    static const int ARRAY_BUFFER;
    static const int DYNAMIC_DRAW;
    static const int ELEMENT_ARRAY_BUFFER;
    static const int FLOAT;
    static const int FRAGMENT_SHADER;
    static const int INT;
    static const int TRIANGLES;
    static const int UNSIGNED_INT;
    static const int VERTEX_SHADER;
};

}