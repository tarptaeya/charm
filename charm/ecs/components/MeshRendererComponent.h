#pragma once

#include "ecs/Component.h"
#include "graphics/geometry/Geometry.h"
#include "graphics/material/Material.h"

namespace charm {

class MeshRendererComponent : public Component {
    Geometry& m_geometry;
    Material& m_material;

public:
    explicit MeshRendererComponent(Entity&, Geometry&, Material&);
    ~MeshRendererComponent() override = default;

    MeshRendererComponent(const MeshRendererComponent&) = delete;
    MeshRendererComponent& operator=(const MeshRendererComponent&) = delete;

    Geometry& get_geometry();
    Material& get_material();
};

}