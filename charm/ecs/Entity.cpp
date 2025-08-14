#include "Entity.h"
#include "components/TransformComponent.h"

namespace charm {

Entity::Entity()
{
    add_component<TransformComponent>();
}

Entity::~Entity()
{
    for (Component* component : m_components)
        delete component;
}

Entity::Entity(Entity&& other)
{
    m_components = std::move(other.m_components);
    other.m_components.clear();
}

Entity& Entity::operator=(Entity&& other)
{
    if (this == &other)
        return *this;

    for (Component* component : m_components)
        delete component;

    m_components = std::move(other.m_components);
    other.m_components.clear();
    return *this;
}

}