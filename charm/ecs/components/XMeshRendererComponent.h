#pragma once

#include "ecs/XComponent.h"
#include "graphics/geometry/XGeometry.h"
#include "graphics/material/XMaterial.h"

class XMeshRendererComponent : public XComponent {
    XGeometry m_geometry;
    XMaterial m_material;

public:
    explicit XMeshRendererComponent(XEntity&, XGeometry&&, XMaterial&&);
    ~XMeshRendererComponent() override = default;

    XMeshRendererComponent(const XMeshRendererComponent&) = delete;
    XMeshRendererComponent& operator=(const XMeshRendererComponent&) = delete;

    XGeometry& get_geometry();
    XMaterial& get_material();
};
