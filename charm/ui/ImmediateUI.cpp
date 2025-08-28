#include "ImmediateUI.h"

namespace charm {

static size_t next_power_of_two(size_t x)
{
    size_t ans = EIGHT_KILO_BYTES;
    while (ans <= x) {
        ans *= 2;
    }
    return ans;
}

ImmediateUI::ImmediateUI()
{
    glGenVertexArrays(1, &m_vertex_array);
    glBindVertexArray(m_vertex_array);

    glGenBuffers(1, &m_array_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_array_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_array_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), 0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(2);
    glVertexAttribIPointer(2, 1, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, active_texture));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));

    glGenBuffers(1, &m_index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);
}

ImmediateUI::~ImmediateUI()
{
    if (m_vertex_array != 0) {
        glDeleteVertexArrays(1, &m_vertex_array);
        glDeleteBuffers(1, &m_array_buffer);
        glDeleteBuffers(1, &m_index_buffer);
    }
}

ImmediateUI::ImmediateUI(ImmediateUI&& other)
{
    m_vertex_array = other.m_vertex_array;
    m_array_buffer = other.m_array_buffer;
    m_index_buffer = other.m_index_buffer;
    other.m_vertex_array = other.m_array_buffer = other.m_index_buffer = 0;

    m_array_buffer_capacity = other.m_array_buffer_capacity;
    m_index_buffer_capacity = other.m_index_buffer_capacity;
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);
}

ImmediateUI& ImmediateUI::operator=(ImmediateUI&& other)
{
    if (this == &other)
        return *this;

    if (m_vertex_array != 0) {
        glDeleteVertexArrays(1, &m_vertex_array);
        glDeleteBuffers(1, &m_array_buffer);
        glDeleteBuffers(1, &m_index_buffer);
    }

    m_vertex_array = other.m_vertex_array;
    m_array_buffer = other.m_array_buffer;
    m_index_buffer = other.m_index_buffer;
    other.m_vertex_array = other.m_array_buffer = other.m_index_buffer = 0;

    m_array_buffer_capacity = other.m_array_buffer_capacity;
    m_index_buffer_capacity = other.m_index_buffer_capacity;
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);

    return *this;
}

void ImmediateUI::begin(int x, int y, int width, int height)
{
    m_vertices.clear();
    m_indices.clear();
}

void ImmediateUI::commit()
{
    if (m_vertices.size() == 0 || m_indices.size() == 0)
        return;

    glBindVertexArray(m_vertex_array);

    if (sizeof(Vertex) * m_vertices.size() > m_array_buffer_capacity) {
        m_array_buffer_capacity = next_power_of_two(sizeof(Vertex) * m_vertices.size());
        glBindBuffer(GL_ARRAY_BUFFER, m_array_buffer);
        glBufferData(GL_ARRAY_BUFFER, m_array_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);
    }
    if (sizeof(unsigned int) * m_indices.size() > m_index_buffer_capacity) {
        m_index_buffer_capacity = next_power_of_two(sizeof(unsigned int) * m_indices.size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_array_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_vertices.size(), &m_vertices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * m_indices.size(), &m_indices[0]);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

void ImmediateUI::add_rect(float x, float y, float width, float height, Color color, int active_texture, Texcoord texcoord_topleft, Texcoord texcoord_bottomright)
{
    unsigned int index = m_vertices.size();

    float u1 = texcoord_topleft.u;
    float v1 = texcoord_topleft.v;
    float u2 = texcoord_bottomright.u;
    float v2 = texcoord_bottomright.v;

    m_vertices.push_back({ x, y, color, active_texture, { u1, v1 } });
    m_vertices.push_back({ x + width, y, color, active_texture, { u2, v1 } });
    m_vertices.push_back({ x + width, y + height, color, active_texture, { u2, v2 } });
    m_vertices.push_back({ x, y + height, color, active_texture, { u1, v2 } });

    m_indices.push_back(index);
    m_indices.push_back(index + 3);
    m_indices.push_back(index + 1);
    m_indices.push_back(index + 1);
    m_indices.push_back(index + 3);
    m_indices.push_back(index + 2);
}

}