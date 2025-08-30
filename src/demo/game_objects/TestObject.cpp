#include "TestObject.h"

TestObject::TestObject(const charm::Matrix4f& transform)
    : m_transform(transform)
{
    m_program = charm::gl::Context::create_program(
        charm::FileIO::read_text("res/demo/basic.vertex.glsl"),
        charm::FileIO::read_text("res/demo/basic.fragment.glsl"));

    m_texture = charm::TextureBuilder("assets/DuckCM.png")
                    .set_texture_unit(GL_TEXTURE0)
                    .build();
}

TestObject::~TestObject()
{
}

void TestObject::render(charm::Camera& camera)
{
    charm::gl::Context::use(m_program);
    charm::gl::Context::set_uniform(m_program, "u_model", m_transform);
    charm::gl::Context::set_uniform(m_program, "u_view", camera.get_view());
    charm::gl::Context::set_uniform(m_program, "u_projection", camera.get_projection());

    charm::gl::Context::bind(GL_TEXTURE_2D, m_texture);

    for (const charm::Geometry& geometry : Duck::get_instance()) {
        geometry.draw();
    }
}

void TestObject::set_transform(const charm::Matrix4f& transform)
{
    m_transform = transform;
}
