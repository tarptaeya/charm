#pragma once

#include "ecs/XComponent.h"
#include "math/XMatrix4f.h"

class XTransformComponent : public XComponent {
    XMatrix4f m_transform = XMatrix4f::identity();

public:
    explicit XTransformComponent(XEntity&);

    XTransformComponent(const XTransformComponent&) = delete;
    XTransformComponent& operator=(const XTransformComponent&) = delete;

    XMatrix4f get_transform() const;
    void set_transform(const XMatrix4f&);
};
