#pragma once

#include "camera/Camera.h"
#include "gl/Context.h"
#include <vector>

namespace charm {

class Skybox {

    gl::Texture m_texture;
    gl::Program m_program;
    gl::VertexArray m_vertex_array;
    gl::Buffer m_array_buffer;
    gl::Buffer m_index_buffer;

public:
    Skybox()
        = default;
    /**
     * @param faces Path to faces of cubemap in the order right, left, top, bottom, front, back
     */
    Skybox(const std::vector<std::string>& faces);
    ~Skybox();

    Skybox(const Skybox&) = delete;
    Skybox& operator=(const Skybox&) = delete;

    Skybox(Skybox&&);
    Skybox& operator=(Skybox&&);

    void render(const Camera&);
};

}