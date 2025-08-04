#pragma once

#include "ecs/Component.h"
#include "math/Matrix4f.h"

namespace charm {

class TransformComponent : public Component {
    Matrix4f m_transform = Matrix4f::identity();

public:
    explicit TransformComponent(Entity&);

    TransformComponent(const TransformComponent&) = delete;
    TransformComponent& operator=(const TransformComponent&) = delete;

    Matrix4f get_transform() const;
    void set_transform(const Matrix4f&);
};

}