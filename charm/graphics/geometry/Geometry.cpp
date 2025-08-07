#include "Geometry.h"

namespace charm {

Geometry::Geometry(GLuint vertex_array, GLuint vertex_buffer, GLuint index_buffer, int count)
    : m_vertex_array(vertex_array)
    , m_vertex_buffer(vertex_buffer)
    , m_index_buffer(index_buffer)
    , m_count(count)
{
}

Geometry::~Geometry()
{
    if (m_vertex_array != 0)
        glDeleteVertexArrays(1, &m_vertex_array);
    if (m_vertex_buffer != 0)
        glDeleteBuffers(1, &m_vertex_buffer);
    if (m_index_buffer != 0)
        glDeleteBuffers(1, &m_index_buffer);
}

Geometry::Geometry(Geometry&& other)
{
    m_vertex_array = other.m_vertex_array;
    m_vertex_buffer = other.m_vertex_buffer;
    m_index_buffer = other.m_index_buffer;
    m_count = other.m_count;
    other.m_vertex_array = other.m_vertex_buffer = other.m_index_buffer = other.m_count = 0;
}

Geometry& Geometry::operator=(Geometry&& other)
{
    if (this == &other)
        return *this;

    m_vertex_array = other.m_vertex_array;
    m_vertex_buffer = other.m_vertex_buffer;
    m_index_buffer = other.m_index_buffer;
    m_count = other.m_count;
    other.m_vertex_array = other.m_vertex_buffer = other.m_index_buffer = other.m_count = 0;
    return *this;
}

void Geometry::draw()
{
    glBindVertexArray(m_vertex_array);
    glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, nullptr);
}

void Geometry::set_vertex_array(GLuint vertex_array)
{
    if (m_vertex_array != 0)
        glDeleteVertexArrays(1, &m_vertex_array);
    m_vertex_array = vertex_array;
}

void Geometry::set_vertex_buffer(GLuint vertex_buffer)
{
    if (m_vertex_buffer != 0)
        glDeleteBuffers(1, &m_vertex_buffer);
    m_vertex_buffer = vertex_buffer;
}

void Geometry::set_index_buffer(GLuint index_buffer)
{
    if (m_index_buffer != 0)
        glDeleteBuffers(1, &m_index_buffer);
    m_index_buffer = index_buffer;
}

void Geometry::set_count(int count)
{
    m_count = count;
}

}