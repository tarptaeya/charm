#include "MeshRendererComponent.h"

namespace charm {

MeshRendererComponent::MeshRendererComponent(Entity& entity, Geometry& geometry, Program& material)
    : Component(entity)
    , m_geometry(geometry)
    , m_program(material)
{
}

Geometry& MeshRendererComponent::get_geometry()
{
    return m_geometry;
}

Program& MeshRendererComponent::get_program()
{
    return m_program;
}

}