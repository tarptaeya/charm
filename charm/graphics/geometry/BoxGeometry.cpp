#include "BoxGeometry.h"

namespace charm {

BoxGeometry::BoxGeometry()
    : Geometry()
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

    set_vertex_array(vertex_array);
    set_vertex_buffer(vertex_buffer);
    set_index_buffer(index_buffer);
    set_count(36);
}

}