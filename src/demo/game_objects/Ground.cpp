#include "Ground.h"

using namespace charm;
using namespace charm::gl;

// clang-format off
float vertices[] = {
    1, 0, 1,
    1, 0, -1,
    -1, 0, -1,
    -1, 0, 1
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};
// clang-format on

Ground::Ground()
{
    m_vertex_array = gen_vertex_array();
    bind(m_vertex_array);

    m_array_buffer = gen_buffer();
    bind(GL_ARRAY_BUFFER, m_array_buffer);
    buffer_data(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    enable_vertex_attrib_array(0);
    vertex_attrib_pointer(0, 3, GL_FLOAT, false, 0, 0);

    m_index_buffer = gen_buffer();
    bind(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    buffer_data(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    m_program = create_program(
        FileIO::read_text("res/demo/ground.vertex.glsl"),
        FileIO::read_text("res/demo/ground.fragment.glsl"));
}

void Ground::update(double delta_time)
{
}

void Ground::render(Camera& camera)
{
    Mat4 transform = Mat4::identity();
    transform *= Mat4::translation(3, 0, 3);
    transform *= Mat4::scaling(5);

    use(m_program);
    set_uniform(m_program, "u_model", transform);
    set_uniform(m_program, "u_view", camera.get_view());
    set_uniform(m_program, "u_projection", camera.get_projection());

    bind(m_vertex_array);
    draw_elements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}