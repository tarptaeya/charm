#include "UIPanel.h"

namespace charm {

static size_t next_power_of_two(size_t x)
{
    size_t ans = EIGHT_KILO_BYTES;
    while (ans <= x) {
        ans *= 2;
    }
    return ans;
}

UIPanel::UIPanel(const FontMetadata& font_metadata)
{
    glGenVertexArrays(1, &m_state.vertex_array);
    glBindVertexArray(m_state.vertex_array);

    glGenBuffers(1, &m_state.array_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_state.array_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_state.array_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), 0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(2);
    glVertexAttribIPointer(2, 1, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, active_texture));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));

    glGenBuffers(1, &m_state.index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_state.index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_state.index_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);

    m_state.font_metadata = font_metadata;
}

UIPanel::~UIPanel()
{
}

UIPanel::UIPanel(UIPanel&& other)
{
}

UIPanel& UIPanel::operator=(UIPanel&& other)
{
    if (this == &other)
        return *this;

    return *this;
}

void UIPanel::draw(int x, int y, int width, int height)
{
    m_state.vertices.clear();
    m_state.indices.clear();
    m_state.xcursor = m_state.ycursor = 0;

#pragma region draw__begin_draw
#pragma endregion

    if (m_state.vertices.size() == 0 || m_state.indices.size() == 0)
        return;

    glBindVertexArray(m_state.vertex_array);

    if (sizeof(Vertex) * m_state.vertices.size() > m_state.array_buffer_capacity) {
        m_state.array_buffer_capacity = next_power_of_two(sizeof(Vertex) * m_state.vertices.size());
        glBindBuffer(GL_ARRAY_BUFFER, m_state.array_buffer);
        glBufferData(GL_ARRAY_BUFFER, m_state.array_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);
    }
    if (sizeof(unsigned int) * m_state.indices.size() > m_state.index_buffer_capacity) {
        m_state.index_buffer_capacity = next_power_of_two(sizeof(unsigned int) * m_state.indices.size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_state.index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_state.index_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_state.array_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_state.vertices.size(), &m_state.vertices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_state.index_buffer);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * m_state.indices.size(), &m_state.indices[0]);
    glDrawElements(GL_TRIANGLES, m_state.indices.size(), GL_UNSIGNED_INT, nullptr);
}

}