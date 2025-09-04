#pragma once

#include "gl/Context.h"
#include <iostream>
#include <vector>

#define FONT_TEXTURE_UNIT 1
#define CANVAS_TEXTURE_UNIT 2
#define ATLAS_TEXTURE_UNIT 3

namespace charm::ui {

#define EIGHT_KILO_BYTES 8192

class Context {
    struct Color {
        float r, g, b;
    };

    struct Texcoord {
        float u, v;
    };

    struct Vertex {
        float x, y;
        Color color;
        int active_texture = 0;
        Texcoord texcoord = { 0 };
    };

    gl::VertexArray m_vertex_array;
    gl::Buffer m_array_buffer;
    gl::Buffer m_index_buffer;
    size_t m_array_buffer_capacity = EIGHT_KILO_BYTES;
    size_t m_index_buffer_capacity = EIGHT_KILO_BYTES;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    Context();

public:
    ~Context();

    Context(const Context&) = delete;
    Context& operator=(Context&) = delete;

    Context(Context&&);
    Context& operator=(Context&&);

    void begin();
    void commit();

    void add_rect(float x, float y, float width, float height, Color color, int active_texture, Texcoord texcoord_topleft, Texcoord texcoord_bottomright);

    static Context& get_instance();
};

}