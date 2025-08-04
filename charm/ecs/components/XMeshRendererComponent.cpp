#include "XMeshRendererComponent.h"

XMeshRendererComponent::XMeshRendererComponent(XEntity& entity, XGeometry&& geometry, XMaterial&& material)
    : XComponent(entity)
    , m_geometry(std::move(geometry))
    , m_material(std::move(material))
{
}

XGeometry& XMeshRendererComponent::get_geometry()
{
    return m_geometry;
}

XMaterial& XMeshRendererComponent::get_material()
{
    return m_material;
}
