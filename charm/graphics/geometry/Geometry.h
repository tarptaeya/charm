#pragma once

#include <glad/gl.h>
#include <vector>

namespace charm {

class Geometry {
    GLuint m_vertex_array = 0;
    int m_count = 0;
    std::vector<GLuint> m_buffers;

public:
    explicit Geometry() = default;
    explicit Geometry(GLuint vertex_array, int count, const std::vector<GLuint>& buffers);
    ~Geometry();

    Geometry(const Geometry&) = delete;
    Geometry& operator=(const Geometry&) = delete;

    Geometry(Geometry&&);
    Geometry& operator=(Geometry&&);

    void draw() const;

    static Geometry box();
};

}