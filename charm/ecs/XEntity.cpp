#include "XEntity.h"
#include "components/XTransformComponent.h"

XEntity::XEntity()
{
    add_component<XTransformComponent>();
}

XEntity::~XEntity()
{
    for (XComponent* component : m_components) {
        delete component;
    }
}

XEntity::XEntity(XEntity&& other)
{
    m_components = std::move(other.m_components);
}

XEntity& XEntity::operator=(XEntity&& other)
{
    if (this == &other)
        return *this;

    m_components = std::move(other.m_components);
    return *this;
}
