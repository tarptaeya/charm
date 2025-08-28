#pragma once

#include "FontMetadata.h"
#include <glad/gl.h>
#include <iostream>
#include <vector>

namespace charm {

#define EIGHT_KILO_BYTES 8192

class ImmediateUI {
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

    unsigned int m_vertex_array = 0;
    unsigned int m_array_buffer = 0;
    unsigned int m_index_buffer = 0;
    size_t m_array_buffer_capacity = EIGHT_KILO_BYTES;
    size_t m_index_buffer_capacity = EIGHT_KILO_BYTES;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

public:
    ImmediateUI();
    ~ImmediateUI();

    ImmediateUI(const ImmediateUI&) = delete;
    ImmediateUI& operator=(ImmediateUI&) = delete;

    ImmediateUI(ImmediateUI&&);
    ImmediateUI& operator=(ImmediateUI&&);

    void begin(int x, int y, int width, int height);
    void commit();

    void add_rect(float x, float y, float width, float height, Color color, int active_texture, Texcoord texcoord_topleft, Texcoord texcoord_bottomright);
};

}