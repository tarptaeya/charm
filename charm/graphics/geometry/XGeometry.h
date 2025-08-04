#pragma once

#include <glad/gl.h>

class XGeometry {
    GLuint m_vertex_array = 0;
    GLuint m_vertex_buffer = 0;
    GLuint m_index_buffer = 0;
    int m_count = 0;

public:
    explicit XGeometry() = default;
    explicit XGeometry(GLuint vertex_array, GLuint vertex_buffer, GLuint index_buffer, int count);
    ~XGeometry();

    XGeometry(const XGeometry&) = delete;
    XGeometry& operator=(const XGeometry&) = delete;

    XGeometry(XGeometry&&);
    XGeometry& operator=(XGeometry&&);

    GLuint get_vertex_array() const;
    int get_count() const;

protected:
    void set_vertex_array(GLuint);
    void set_vertex_buffer(GLuint);
    void set_index_buffer(GLuint);
    void set_count(int);
};
