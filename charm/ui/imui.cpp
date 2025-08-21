#include "imui.h"
#include <glad/gl.h>
#include <iostream>
#include <vector>

namespace charm::imui {

#define EIGHT_KILO_BYTES 8192

struct Color {
    float r, g, b;
};

struct Texcoord {
    float u, v;
};

struct Vertex {
    float x, y;
    Color color = { 0 };
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

    ~State()
    {
        if (vertex_array != 0) {
            glDeleteBuffers(1, &array_buffer);
            glDeleteBuffers(1, &index_buffer);
            glDeleteVertexArrays(1, &vertex_array);
        }
    }

    void add_rect(float x, float y, float width, float height, Color color, int active_texture, Texcoord texcoord_topleft, Texcoord texcoord_bottomright)
    {
        unsigned int index = vertices.size();

        float u1 = texcoord_topleft.u;
        float v1 = texcoord_topleft.v;
        float u2 = texcoord_bottomright.u;
        float v2 = texcoord_bottomright.v;

        vertices.push_back({ x, y, color, active_texture, { u1, v1 } });
        vertices.push_back({ x + width, y, color, active_texture, { u2, v1 } });
        vertices.push_back({ x + width, y + height, color, active_texture, { u2, v2 } });
        vertices.push_back({ x, y + height, color, active_texture, { u1, v2 } });

        indices.push_back(index);
        indices.push_back(index + 3);
        indices.push_back(index + 1);
        indices.push_back(index + 1);
        indices.push_back(index + 3);
        indices.push_back(index + 2);
    }
};

size_t next_power_of_two(size_t x)
{
    size_t ans = EIGHT_KILO_BYTES;
    while (ans <= x) {
        ans *= 2;
    }
    return ans;
}

static State s_state;

void begin(int x, int y, int width, int height, const FontMetadata& metadata)
{
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        glGenVertexArrays(1, &s_state.vertex_array);
        glBindVertexArray(s_state.vertex_array);

        glGenBuffers(1, &s_state.array_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, s_state.array_buffer);
        glBufferData(GL_ARRAY_BUFFER, s_state.array_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(2);
        glVertexAttribIPointer(2, 1, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, active_texture));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));

        glGenBuffers(1, &s_state.index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_state.index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_state.index_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);

        glBindVertexArray(0);
    }

    s_state.vertices.clear();
    s_state.indices.clear();
    s_state.font_metadata = metadata;
    s_state.xcursor = x;
    s_state.ycursor = y;

    s_state.add_rect(x, y, width, height, { 0.4, 0.5, 0.6 }, 0, { 0, 0 }, { 0, 0 });
}

void end()
{
    if (s_state.vertices.size() == 0 || s_state.indices.size() == 0)
        return;

    glBindVertexArray(s_state.vertex_array);

    if (sizeof(Vertex) * s_state.vertices.size() > s_state.array_buffer_capacity) {
        s_state.array_buffer_capacity = next_power_of_two(sizeof(Vertex) * s_state.vertices.size());
        glBindBuffer(GL_ARRAY_BUFFER, s_state.array_buffer);
        glBufferData(GL_ARRAY_BUFFER, s_state.array_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);
    }

    if (sizeof(unsigned int) * s_state.indices.size() > s_state.index_buffer_capacity) {
        s_state.index_buffer_capacity = next_power_of_two(sizeof(unsigned int) * s_state.indices.size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_state.index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_state.index_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, s_state.array_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * s_state.vertices.size(), &s_state.vertices[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_state.index_buffer);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * s_state.indices.size(), &s_state.indices[0]);

    glDrawElements(GL_TRIANGLES, s_state.indices.size(), GL_UNSIGNED_INT, nullptr);
}

void label(const std::string& text, float font_size)
{
    float bitmap_pixel_height = 64;

    s_state.ycursor += font_size;
    int xcurr = s_state.xcursor;
    int ycurr = s_state.ycursor;
    static bool debug = false;

    for (char c : text) {
        const auto& info = s_state.font_metadata.info[c];

        float u1 = info.x / (float)s_state.font_metadata.bitmap_width;
        float v1 = 1 - info.y / (float)s_state.font_metadata.bitmap_height;
        float u2 = (info.x + info.width) / (float)s_state.font_metadata.bitmap_width;
        float v2 = 1 - (info.y + info.height) / (float)s_state.font_metadata.bitmap_height;

        float x = xcurr + info.xoffset * font_size / s_state.font_metadata.bitmap_pixel_height;
        float y = ycurr + info.yoffset * font_size / s_state.font_metadata.bitmap_pixel_height;
        float width = info.width * font_size / s_state.font_metadata.bitmap_pixel_height;
        float height = info.height * font_size / s_state.font_metadata.bitmap_pixel_height;
        s_state.add_rect(x, y, width, height, { 1, 0, 0 }, 1, { u1, v1 }, { u2, v2 });
        xcurr += info.xadvance * font_size / s_state.font_metadata.bitmap_pixel_height;
    }
}

}
