#include "MeshRendererComponent.h"

namespace charm {

MeshRendererComponent::MeshRendererComponent(Entity& entity, Geometry& geometry, Shader& shader)
    : Component(entity)
    , m_geometry(geometry)
    , m_shader(shader)
{
}

Geometry& MeshRendererComponent::get_geometry()
{
    return m_geometry;
}

Shader& MeshRendererComponent::get_shader()
{
    return m_shader;
}

}