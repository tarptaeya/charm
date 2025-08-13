#pragma once

#include "ecs/Component.h"
#include "graphics/geometry/Geometry.h"
#include "graphics/shaders/Program.h"

namespace charm {

class MeshRendererComponent : public Component {
    Geometry& m_geometry;
    Program& m_program;

public:
    explicit MeshRendererComponent(Entity&, Geometry&, Program&);
    ~MeshRendererComponent() override = default;

    MeshRendererComponent(const MeshRendererComponent&) = delete;
    MeshRendererComponent& operator=(const MeshRendererComponent&) = delete;

    Geometry& get_geometry();
    Program& get_program();
};

}