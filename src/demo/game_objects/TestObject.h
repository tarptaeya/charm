#pragma once

#include "Duck.h"
#include "IGameObject.h"
#include "charm.h"

class TestObject : public IGameObject {
    charm::gl::Program m_program;
    charm::Matrix4f m_transform;
    charm::Texture2D m_texture;

public:
    TestObject(const charm::Matrix4f& transform);

    ~TestObject() override;

    void render(charm::Camera& camera) override;

    void set_transform(const charm::Matrix4f& transform);
};
