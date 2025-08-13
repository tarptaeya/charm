#pragma once

#include "ecs/Component.h"
#include "graphics/geometry/Geometry.h"
#include "graphics/shaders/Shader.h"

namespace charm {

class MeshRendererComponent : public Component {
    Geometry& m_geometry;
    Shader& m_shader;

public:
    explicit MeshRendererComponent(Entity&, Geometry&, Shader&);
    ~MeshRendererComponent() override = default;

    MeshRendererComponent(const MeshRendererComponent&) = delete;
    MeshRendererComponent& operator=(const MeshRendererComponent&) = delete;

    Geometry& get_geometry();
    Shader& get_shader();
};

}