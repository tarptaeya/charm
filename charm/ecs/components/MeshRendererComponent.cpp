#include "MeshRendererComponent.h"

namespace charm {

MeshRendererComponent::MeshRendererComponent(Entity& entity, Geometry& geometry, Material& material)
    : Component(entity)
    , m_geometry(geometry)
    , m_material(material)
{
}

Geometry& MeshRendererComponent::get_geometry()
{
    return m_geometry;
}

Material& MeshRendererComponent::get_material()
{
    return m_material;
}

}