#include "TestObject.h"

TestObject::TestObject(const charm::Mat4& transform)
    : m_transform(transform)
{
    m_character = charm::Model("res/demo/model.ch3db");
    m_character.set_current_animation(m_character.get_animations()[0]);

    m_program = charm::gl::create_program(
        charm::FileIO::read_text("res/demo/basic.vertex.glsl"),
        charm::FileIO::read_text("res/demo/basic.fragment.glsl"));

    m_texture = charm::TextureBuilder("res/demo/diffuse.jpg").build();
}

TestObject::~TestObject()
{
}

void TestObject::update(double delta_time)
{
    m_character.update(delta_time);
}

void TestObject::render(charm::Camera& camera, charm::Environment& environment)
{
    charm::gl::use(m_program);
    charm::gl::set_uniform(m_program, "u_model", m_transform);
    charm::gl::set_uniform(m_program, "u_view", camera.get_view());
    charm::gl::set_uniform(m_program, "u_projection", camera.get_projection());
    m_character.set_joint_uniforms(m_program);
    environment.set_uniforms(m_program);

    charm::gl::bind(GL_TEXTURE_2D, m_texture);
    m_character.draw();
}

void TestObject::set_transform(const charm::Mat4& transform)
{
    m_transform = transform;
}
