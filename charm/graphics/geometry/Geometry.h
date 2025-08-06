#pragma once

#include <glad/gl.h>

namespace charm {

class Geometry {
    GLuint m_vertex_array = 0;
    GLuint m_vertex_buffer = 0;
    GLuint m_index_buffer = 0;
    int m_count = 0;

public:
    explicit Geometry() = default;
    explicit Geometry(GLuint vertex_array, GLuint vertex_buffer, GLuint index_buffer, int count);
    ~Geometry();

    Geometry(const Geometry&) = delete;
    Geometry& operator=(const Geometry&) = delete;

    Geometry(Geometry&&);
    Geometry& operator=(Geometry&&);

    GLuint get_vertex_array() const;
    int get_count() const;

protected:
    void set_vertex_array(GLuint);
    void set_vertex_buffer(GLuint);
    void set_index_buffer(GLuint);
    void set_count(int);
};

}