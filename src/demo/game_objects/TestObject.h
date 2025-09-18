#pragma once

#include "IGameObject.h"
#include "charm.h"

class TestObject : public IGameObject {
    charm::Model m_character;
    charm::gl::Program m_program;
    charm::Mat4 m_transform;
    charm::gl::Texture m_texture;

public:
    TestObject(const charm::Mat4& transform);

    ~TestObject() override;

    void update(double delta_time) override;
    void render(charm::Camera& camera) override;

    void set_transform(const charm::Mat4& transform);
};
