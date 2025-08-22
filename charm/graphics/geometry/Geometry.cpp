#include "Geometry.h"

namespace charm {

Geometry::Geometry(GLuint vertex_array, int count, const std::vector<GLuint>& buffers)
    : m_vertex_array(vertex_array)
    , m_count(count)
    , m_buffers(buffers)
{
}

Geometry::~Geometry()
{
    if (m_vertex_array != 0)
        glDeleteVertexArrays(1, &m_vertex_array);

    if (m_buffers.size() > 0)
        glDeleteBuffers(m_buffers.size(), &m_buffers[0]);
}

Geometry::Geometry(Geometry&& other)
{
    m_vertex_array = other.m_vertex_array;
    m_count = other.m_count;
    other.m_vertex_array = other.m_count = 0;
    m_buffers = std::move(other.m_buffers);
    other.m_buffers.clear();
}

Geometry& Geometry::operator=(Geometry&& other)
{
    if (this == &other)
        return *this;

    if (m_vertex_array != 0)
        glDeleteVertexArrays(1, &m_vertex_array);

    if (m_buffers.size() > 0)
        glDeleteBuffers(m_buffers.size(), &m_buffers[0]);

    m_vertex_array = other.m_vertex_array;
    m_count = other.m_count;
    other.m_vertex_array = other.m_count = 0;
    m_buffers = std::move(other.m_buffers);
    other.m_buffers.clear();
    return *this;
}

void Geometry::draw() const
{
    glBindVertexArray(m_vertex_array);
    glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, nullptr);
}

Geometry Geometry::box()
{
    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // clang-format off
    float data[] = {
        -0.5, 0.5, 0.5, 0, 0, 0, 0, 1,
        0.5, 0.5, 0.5, 1, 0, 0, 0, 1,
        0.5, -0.5, 0.5, 1, 1, 0, 0, 1,
        -0.5, -0.5, 0.5, 0, 1, 0, 0, 1,

        -0.5, 0.5, -0.5, 1, 0, 0, 0, -1,
        0.5, 0.5, -0.5, 0, 0, 0, 0, -1,
        0.5, -0.5, -0.5, 0, 1, 0, 0, -1,
        -0.5, -0.5, -0.5, 1, 1, 0, 0, -1,

        -0.5, 0.5, -0.5, 0, 0, 0, 1, 0,
        0.5, 0.5, -0.5, 1, 0, 0, 1, 0,
        0.5, 0.5, 0.5, 1, 1, 0, 1, 0,
        -0.5, 0.5, 0.5, 0, 1, 0, 1, 0,

        -0.5, -0.5, -0.5, 1, 0, 0, -1, 0,
        0.5, -0.5, -0.5, 0, 0, 0, -1, 0,
        0.5, -0.5, 0.5, 0, 1, 0, -1, 0,
        -0.5, -0.5, 0.5, 1, 1, 0, -1, 0,

        -0.5, 0.5, 0.5, 1, 0, -1, 0, 0,
        -0.5, -0.5, 0.5, 1, 1, -1, 0, 0,
        -0.5, -0.5, -0.5, 0, 1, -1, 0, 0,
        -0.5, 0.5, -0.5, 0, 0, -1, 0, 0,

        0.5, 0.5, 0.5, 0, 0, 1, 0, 0,
        0.5, -0.5, 0.5, 0, 1, 1, 0, 0,
        0.5, -0.5, -0.5, 1, 1, 1, 0, 0,
        0.5, 0.5, -0.5, 1, 0, 1, 0, 0,
    };
    // clang-format on
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(5 * sizeof(float)));

    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    // clang-format off
    unsigned int indices[] = {
        0, 2, 1, 0, 3, 2,
        4, 5, 6, 4, 6, 7,
        8, 10, 9, 8, 11, 10,
        12, 13, 14, 12, 14, 15,
        19, 17, 16, 19, 18, 17,
        20, 22, 23, 20, 21, 22,
    };
    // clang-format on
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    std::vector<GLuint> buffers { vertex_buffer, index_buffer };
    return Geometry(vertex_array, 36, buffers);
}

}