#pragma once

#include "gl/Context.h"
#include "graphics/font/Font.h"
#include "misc/misc.h"
#include <iostream>
#include <vector>

#define FONT_TEXTURE_UNIT 1
#define CANVAS_TEXTURE_UNIT 2
#define ATLAS_TEXTURE_UNIT 3

namespace charm::ui {

#define EIGHT_KILO_BYTES 8192

class Context {
public:
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

        Rect& clip(float clip_x, float clip_y, float clip_width, float clip_height)
        {
            float ans_x1 = x;
            float ans_y1 = y;
            float ans_x2 = x + width;
            float ans_y2 = y + height;

            float ans_u1 = texcoords[0].u;
            float ans_v1 = texcoords[0].v;
            float ans_u2 = texcoords[1].u;
            float ans_v2 = texcoords[1].v;

            if (x < clip_x) {
                ans_x1 = clip_x;
                ans_u1 = std::min(1.0f, (texcoords[1].u - texcoords[0].u) * (clip_x - x) / width + texcoords[0].u);
            }

            if (clip_x + clip_width < x + width) {
                ans_x2 = clip_x + clip_width;
                ans_u2 = std::min(1.0f, (texcoords[1].u - texcoords[0].u) * (clip_x + clip_width - x) / width + texcoords[0].u);
            }

            if (y < clip_y) {
                ans_y1 = clip_y;
                ans_v1 = std::min(1.0f, (texcoords[1].v - texcoords[0].v) * (clip_y - y) / height + texcoords[0].v);
            }

            if (clip_y + clip_height < y + height) {
                ans_y2 = clip_y + clip_height;
                ans_v2 = std::min(1.0f, (texcoords[1].v - texcoords[0].v) * (clip_y + clip_height - y) / height + texcoords[0].v);
            }

            x = ans_x1;
            y = ans_y1;
            width = ans_x2 - ans_x1;
            height = ans_y2 - ans_y1;
            texcoords[0].u = ans_u1;
            texcoords[0].v = ans_v1;
            texcoords[1].u = ans_u2;
            texcoords[1].v = ans_v2;

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