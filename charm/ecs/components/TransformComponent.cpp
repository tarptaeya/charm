#include "TransformComponent.h"

namespace charm {

TransformComponent::TransformComponent(Entity& entity)
    : Component(entity)
{
}

Matrix4f TransformComponent::get_transformation_matrix()
{
    static float theta = 0;
    theta += 0.01;

    Matrix4f model = Matrix4f::identity();
    model *= Matrix4f::rotation_x(theta) * Matrix4f::rotation_y(theta) * Matrix4f::rotation_z(theta);
    return model;
}

}
