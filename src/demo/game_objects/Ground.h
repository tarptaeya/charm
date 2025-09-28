#pragma once

#include "IGameObject.h"
#include "charm.h"

class Ground : public IGameObject {
    charm::gl::VertexArray m_vertex_array;
    charm::gl::Buffer m_array_buffer;
    charm::gl::Buffer m_index_buffer;
    charm::gl::Program m_program;

public:
    Ground();

    Ground(const Ground&) = delete;
    Ground& operator=(const Ground&) = delete;

    void update(double delta_time) override;
    void render(charm::Camera&, charm::Environment&) override;
};