#include "TransformComponent.h"

namespace charm {

TransformComponent::TransformComponent(Entity& entity)
    : Component(entity)
{
}

Matrix4f TransformComponent::get_transform() const
{
    return m_transform;
}

void TransformComponent::set_transform(const Matrix4f& transform)
{
    m_transform = transform;
}

}