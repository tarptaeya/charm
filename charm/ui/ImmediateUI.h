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

    struct State {
        unsigned int vertex_array = 0;
        unsigned int array_buffer = 0;
        unsigned int index_buffer = 0;
        size_t array_buffer_capacity = EIGHT_KILO_BYTES;
        size_t index_buffer_capacity = EIGHT_KILO_BYTES;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        float xcursor = 0;
        float ycursor = 0;
        FontMetadata font_metadata;

        ~State();
    };

    State m_state = { 0 };

public:
    ImmediateUI() = default;
    ImmediateUI(const FontMetadata&);
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