#include "XTransformComponent.h"

XTransformComponent::XTransformComponent(XEntity& entity)
    : XComponent(entity)
{
}

XMatrix4f XTransformComponent::get_transform() const
{
    return m_transform;
}

void XTransformComponent::set_transform(const XMatrix4f& transform)
{
    m_transform = transform;
}
