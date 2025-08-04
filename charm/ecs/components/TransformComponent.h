#pragma once

#include "ecs/Component.h"
#include "math/Matrix4f.h"

namespace charm {

class TransformComponent : public Component {
public:
    explicit TransformComponent(Entity&);

    TransformComponent(const TransformComponent&) = delete;
    TransformComponent& operator=(const TransformComponent&) = delete;

    Matrix4f get_transformation_matrix();
};

}