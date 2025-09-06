#pragma once

#include "gl/Context.h"
#include "graphics/font/Font.h"
#include <iostream>
#include <vector>

#define FONT_TEXTURE_UNIT 1
#define CANVAS_TEXTURE_UNIT 2
#define ATLAS_TEXTURE_UNIT 3

namespace charm::ui {

#define EIGHT_KILO_BYTES 8192

class Context {
public:
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

    struct Rect {
        float x, y, width, height;
        Color color;
        int active_texture = 0;
        Texcoord texcoords[2] = { 0 };

        Rect(float x, float y, float width, float height)
            : x(x)
            , y(y)
            , width(width)
            , height(height)
        {
        }

        Rect& set_color(Color color)
        {
            this->color = color;
            return *this;
        }

        Rect& set_texcoords(Texcoord topleft, Texcoord bottomright)
        {
            this->texcoords[0] = topleft;
            this->texcoords[1] = bottomright;
            return *this;
        }

        Rect& set_active_texture(unsigned int index)
        {
            this->active_texture = index;
            return *this;
        }
    };

private:
    gl::VertexArray m_vertex_array;
    gl::Buffer m_array_buffer;
    gl::Buffer m_index_buffer;
    size_t m_array_buffer_capacity = EIGHT_KILO_BYTES;
    size_t m_index_buffer_capacity = EIGHT_KILO_BYTES;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    std::unique_ptr<Font> m_font = nullptr;
    gl::Program m_program;

    Context();

public:
    ~Context();

    Context(const Context&) = delete;
    Context& operator=(Context&) = delete;

    Context(Context&&);
    Context& operator=(Context&&);

    [[nodiscard]] Font& get_font();
    [[nodiscard]] gl::Program& get_program();

    void begin();
    void commit();

    void add_rect(float x, float y, float width, float height, Color color, int active_texture, Texcoord texcoord_topleft, Texcoord texcoord_bottomright);
    void add_rect(const Rect&);

    static Context& get_instance();

private:
    void setup_buffers();
    void draw();
};

}