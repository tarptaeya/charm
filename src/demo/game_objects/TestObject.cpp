#include "TestObject.h"

TestObject::TestObject(const charm::Matrix4f& transform)
    : m_shader(charmShaders.get("basic"))
    , m_transform(transform)
{
    m_texture = charm::Texture2DBuilder("assets/DuckCM.png")
                    .set_texture_unit(GL_TEXTURE0)
                    .build();
}

TestObject::~TestObject()
{
}

void TestObject::render(charm::Camera& camera)
{
    m_shader.use();
    m_shader.set_uniform("u_model", m_transform);
    m_shader.set_uniform("u_view", camera.get_view());
    m_shader.set_uniform("u_projection", camera.get_projection());

    m_texture.bind();
    for (const charm::Geometry& geometry : Duck::get_instance()) {
        geometry.draw();
    }
}

void TestObject::set_transform(const charm::Matrix4f& transform)
{
    m_transform = transform;
}
