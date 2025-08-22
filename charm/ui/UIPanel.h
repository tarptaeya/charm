#pragma once

#include "FontMetadata.h"
#include <glad/gl.h>
#include <iostream>
#include <vector>

namespace charm {

#define EIGHT_KILO_BYTES 8192

class UIPanel {

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
    };

    State m_state = { 0 };

public:
    UIPanel(const FontMetadata& font_metadata);
    ~UIPanel();

    UIPanel(const UIPanel&) = delete;
    UIPanel& operator=(UIPanel&) = delete;

    UIPanel(UIPanel&&);
    UIPanel& operator=(UIPanel&&);

    void draw(int x, int y, int width, int height);
};

}