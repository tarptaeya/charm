#include "MeshRendererComponent.h"

namespace charm {

MeshRendererComponent::MeshRendererComponent(charm::Entity& entity, charm::Geometry&& geometry, charm::Material&& material)
    : Component(entity)
    , m_geometry(std::move(geometry))
    , m_material(std::move(material))
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