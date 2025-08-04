#pragma once

#include "ecs/Component.h"
#include "graphics/geometry/Geometry.h"
#include "graphics/material/Material.h"

namespace charm {

class MeshRendererComponent : public Component {
    charm::Geometry m_geometry;
    charm::Material m_material;

public:
    explicit MeshRendererComponent(charm::Entity&, charm::Geometry&&, charm::Material&&);
    ~MeshRendererComponent() override = default;

    MeshRendererComponent(const MeshRendererComponent&) = delete;
    MeshRendererComponent& operator=(const MeshRendererComponent&) = delete;

    charm::Geometry& get_geometry();
    charm::Material& get_material();
};

}