#include "ScreenGeometry.h"

ScreenGeometry::ScreenGeometry()
{
    unsigned int vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    unsigned int vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // clang-format off
            float vertices[] = {
                -1, -1, 0, 0,
                -1, 1, 0, 1,
                1, 1, 1, 1,
                1, -1, 1, 0,
            };
    // clang-format on
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    unsigned int index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    // clang-format off
            unsigned int indices[] = {
                0, 2, 1,
                0, 3, 2,
            };
    // clang-format on
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    m_geometry = charm::Geometry(vertex_array, 6, { vertex_buffer, index_buffer });
}

ScreenGeometry::~ScreenGeometry()
{
}

ScreenGeometry::ScreenGeometry(ScreenGeometry&& other)
{
    m_geometry = std::move(other.m_geometry);
}

ScreenGeometry& ScreenGeometry::operator=(ScreenGeometry&& other)
{
    if (this == &other)
        return *this;

    m_geometry = std::move(other.m_geometry);
    return *this;
}

const charm::Geometry& ScreenGeometry::get_geometry() const
{
    return m_geometry;
}

ScreenGeometry& ScreenGeometry::get_instance()
{
    static ScreenGeometry screen;
    return screen;
}