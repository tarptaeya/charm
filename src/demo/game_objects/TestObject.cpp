#include "TestObject.h"

TestObject::TestObject(const charm::Mat4& transform)
    : m_transform(transform)
{
    m_character = new Character;

    m_program = charm::gl::create_program(
        charm::FileIO::read_text("res/demo/basic.vertex.glsl"),
        charm::FileIO::read_text("res/demo/basic.fragment.glsl"));

    m_texture = charm::TextureBuilder("res/demo/diffuse.jpg").build();
}

TestObject::~TestObject()
{
    delete m_character;
}

void TestObject::update(double delta_time)
{
    m_character->update(delta_time);
}

void TestObject::render(charm::Camera& camera)
{
    charm::gl::use(m_program);
    charm::gl::set_uniform(m_program, "u_model", m_transform);
    charm::gl::set_uniform(m_program, "u_view", camera.get_view());
    charm::gl::set_uniform(m_program, "u_projection", camera.get_projection());
    m_character->setup_joint_uniform(m_program);

    charm::gl::bind(GL_TEXTURE_2D, m_texture);

    for (const charm::Geometry& geometry : *m_character) {
        geometry.draw();
    }
}

void TestObject::set_transform(const charm::Mat4& transform)
{
    m_transform = transform;
}
