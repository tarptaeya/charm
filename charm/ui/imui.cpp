#include "imui.h"
#include <glad/gl.h>
#include <vector>

namespace charm::imui {

#define EIGHT_KILO_BYTES 8192

struct Color {
    float r, g, b;
};

struct Vertex {
    float x, y;
    Color color;
};

struct State {
    unsigned int vertex_array = 0;
    unsigned int array_buffer = 0;
    unsigned int index_buffer = 0;
    size_t array_buffer_capacity = EIGHT_KILO_BYTES;
    size_t index_buffer_capacity = EIGHT_KILO_BYTES;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    ~State()
    {
        if (vertex_array != 0) {
            glDeleteBuffers(1, &array_buffer);
            glDeleteBuffers(1, &index_buffer);
            glDeleteVertexArrays(1, &vertex_array);
        }
    }

    void add_rect(float x, float y, float width, float height, Color color)
    {
        unsigned int index = vertices.size();

        vertices.push_back({ x, y, color });
        vertices.push_back({ x + width, y, color });
        vertices.push_back({ x + width, y + height, color });
        vertices.push_back({ x, y + height, color });

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

void begin(int x, int y, int width, int height)
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
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * sizeof(float), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)(2 * sizeof(float)));

        glGenBuffers(1, &s_state.index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_state.index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_state.index_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);

        glBindVertexArray(0);
    }

    s_state.vertices.clear();
    s_state.indices.clear();

    s_state.add_rect(x, y, width, height, { 0.4, 0.5, 0.6 });
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

}
