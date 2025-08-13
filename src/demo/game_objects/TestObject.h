#pragma once

#include "IGameObject.h"
#include "charm.h"

class TestObject : public IGameObject {
    charm::Shader& m_shader;
    charm::Matrix4f m_transform;

public:
    TestObject(const charm::Matrix4f& transform)
        : m_shader(charmShaders.get("basic"))
        , m_transform(transform)
    {
    }

    ~TestObject() override { }

    void render(charm::Camera& camera) override
    {
        m_shader.use();
        m_shader.set_uniform("u_model", m_transform);
        m_shader.set_uniform("u_view", camera.get_view());
        m_shader.set_uniform("u_projection", camera.get_projection());

        for (int i = 0; i < 1; ++i) {
            charmGeometries.get("model." + std::to_string(i)).draw();
        }
    }

    void set_transform(const charm::Matrix4f& transform)
    {
        m_transform = transform;
    }
};
