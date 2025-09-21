#include "Skybox.h"
#include "io/FileIO.h"
#include "misc/stb_image.h"
#include <iostream>

namespace charm {

static float vertices[] = {
    // clang-format off
    -1, 1, 1,
    1, 1, 1,
    1, -1, 1,
    -1, -1, 1,

    -1, 1, -1,
    1, 1, -1,
    1, -1, -1,
    -1, -1, -1,

    -1, 1, -1,
    1, 1, -1,
    1, 1, 1,
    -1, 1, 1,

    -1, -1, -1,
    1, -1, -1,
    1, -1, 1,
    -1, -1, 1,

    -1, 1, 1,
    -1, -1, 1,
    -1, -1, -1,
    -1, 1, -1,

    1, 1, 1,
    1, -1, 1,
    1, -1, -1,
    1, 1, -1,
    // clang-format on
};

static unsigned int indices[] = {
    // clang-format off
    0, 2, 1, 0, 3, 2,
    4, 5, 6, 4, 6, 7,
    8, 10, 9, 8, 11, 10,
    12, 13, 14, 12, 14, 15,
    19, 17, 16, 19, 18, 17,
    20, 22, 23, 20, 21, 22,
    // clang-format on
};

Skybox::Skybox(const std::vector<std::string>& faces)
{
    stbi_set_flip_vertically_on_load(false);

    m_texture = gl::gen_texture();
    gl::bind(GL_TEXTURE_CUBE_MAP, m_texture);
    gl::tex_parameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl::tex_parameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl::tex_parameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl::tex_parameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl::tex_parameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (int i = 0; i < faces.size(); ++i) {
        int width, height, channels;
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 3);
        if (!data) {
            std::cerr << "[error] unable to read image: " << faces[i] << std::endl;
            std::cerr << stbi_failure_reason() << std::endl;
            std::exit(0);
        }

        gl::tex_image2d(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    m_program = gl::create_program(FileIO::read_text("res/charm/skybox.vertex.glsl"), FileIO::read_text("res/charm/skybox.fragment.glsl"));

    m_vertex_array = gl::gen_vertex_array();
    gl::bind(m_vertex_array);

    m_array_buffer = gl::gen_buffer();
    gl::bind(GL_ARRAY_BUFFER, m_array_buffer);
    gl::buffer_data(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    gl::enable_vertex_attrib_array(0);
    gl::vertex_attrib_pointer(0, 3, GL_FLOAT, false, 0, 0);

    m_index_buffer = gl::gen_buffer();
    gl::bind(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    gl::buffer_data(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

Skybox::~Skybox()
{
}

Skybox::Skybox(Skybox&& other)
{
    m_texture = std::move(other.m_texture);
    m_program = std::move(other.m_program);
    m_vertex_array = std::move(other.m_vertex_array);
    m_array_buffer = std::move(other.m_array_buffer);
    m_index_buffer = std::move(other.m_index_buffer);
}

Skybox& Skybox::operator=(Skybox&& other)
{
    if (this == &other)
        return *this;

    m_texture = std::move(other.m_texture);
    m_program = std::move(other.m_program);
    m_vertex_array = std::move(other.m_vertex_array);
    m_array_buffer = std::move(other.m_array_buffer);
    m_index_buffer = std::move(other.m_index_buffer);

    return *this;
}

void Skybox::render(const Camera& camera)
{
    gl::depth_mask(GL_FALSE);

    gl::use(m_program);
    charm::gl::set_uniform(m_program, "u_view", camera.get_view());
    charm::gl::set_uniform(m_program, "u_projection", camera.get_projection());

    gl::bind(GL_TEXTURE_CUBE_MAP, m_texture);

    gl::bind(m_vertex_array);
    gl::draw_elements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    gl::depth_mask(GL_TRUE);
}

}