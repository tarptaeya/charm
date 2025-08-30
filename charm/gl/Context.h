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

    Shader create_shader(int type, const std::string& source) const;
    Program create_program(const std::string& vertex_source, const std::string& fragment_source) const;
    void use(const Program& program) const;

    VertexArray gen_vertex_array() const;
    void bind(const VertexArray& vertex_array) const;
    void enable_vertex_attrib_array(unsigned int index) const;
    void vertex_attrib_pointer(unsigned int index, int size, int type, bool normalized, int stride, const void* pointer) const;
    void vertex_attribi_pointer(unsigned int index, int size, int type, int stride, const void* pointer) const;

    Buffer gen_buffer() const;
    void bind(int type, const Buffer& buffer) const;
    void buffer_data(int type, int size, const void* data, int usage);

    static const int ARRAY_BUFFER;
    static const int ELEMENT_ARRAY_BUFFER;
    static const int FRAGMENT_SHADER;
    static const int VERTEX_SHADER;
};

}