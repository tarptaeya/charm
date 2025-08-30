#include "Context.h"

namespace charm::ui {

static size_t next_power_of_two(size_t x)
{
    size_t ans = EIGHT_KILO_BYTES;
    while (ans <= x) {
        ans *= 2;
    }
    return ans;
}

Context::Context()
{
    m_vertex_array = gl::Context::gen_vertex_array();
    gl::Context::bind(m_vertex_array);

    m_array_buffer = gl::Context::gen_buffer();
    gl::Context::bind(GL_ARRAY_BUFFER, m_array_buffer);
    gl::Context::buffer_data(GL_ARRAY_BUFFER, m_array_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);

    gl::Context::enable_vertex_attrib_array(0);
    gl::Context::vertex_attrib_pointer(0, 2, GL_FLOAT, false, sizeof(Vertex), 0);
    gl::Context::enable_vertex_attrib_array(1);
    gl::Context::vertex_attrib_pointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
    gl::Context::enable_vertex_attrib_array(2);
    gl::Context::vertex_attribi_pointer(2, 1, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, active_texture));
    gl::Context::enable_vertex_attrib_array(3);
    gl::Context::vertex_attrib_pointer(3, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));

    m_index_buffer = gl::Context::gen_buffer();
    gl::Context::bind(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    gl::Context::buffer_data(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);
}

Context::~Context()
{
}

Context::Context(Context&& other)
{
    m_vertex_array = std::move(other.m_vertex_array);
    m_array_buffer = std::move(other.m_array_buffer);
    m_index_buffer = std::move(other.m_index_buffer);

    m_array_buffer_capacity = other.m_array_buffer_capacity;
    m_index_buffer_capacity = other.m_index_buffer_capacity;
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);
}

Context& Context::operator=(Context&& other)
{
    if (this == &other)
        return *this;

    m_vertex_array = std::move(other.m_vertex_array);
    m_array_buffer = std::move(other.m_array_buffer);
    m_index_buffer = std::move(other.m_index_buffer);

    m_array_buffer_capacity = other.m_array_buffer_capacity;
    m_index_buffer_capacity = other.m_index_buffer_capacity;
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);

    return *this;
}

void Context::begin()
{
    m_vertices.clear();
    m_indices.clear();
}

void Context::commit()
{
    if (m_vertices.size() == 0 || m_indices.size() == 0)
        return;

    gl::Context::bind(m_vertex_array);

    if (sizeof(Vertex) * m_vertices.size() > m_array_buffer_capacity) {
        m_array_buffer_capacity = next_power_of_two(sizeof(Vertex) * m_vertices.size());
        gl::Context::bind(GL_ARRAY_BUFFER, m_array_buffer);
        gl::Context::buffer_data(GL_ARRAY_BUFFER, m_array_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);
    }
    if (sizeof(unsigned int) * m_indices.size() > m_index_buffer_capacity) {
        m_index_buffer_capacity = next_power_of_two(sizeof(unsigned int) * m_indices.size());
        gl::Context::bind(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
        gl::Context::buffer_data(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_capacity, nullptr, GL_DYNAMIC_DRAW);
    }

    gl::Context::bind(GL_ARRAY_BUFFER, m_array_buffer);
    gl::Context::buffer_sub_data(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_vertices.size(), &m_vertices[0]);
    gl::Context::bind(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    gl::Context::buffer_sub_data(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * m_indices.size(), &m_indices[0]);
    gl::Context::draw_elements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Context::add_rect(float x, float y, float width, float height, Color color, int active_texture, Texcoord texcoord_topleft, Texcoord texcoord_bottomright)
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