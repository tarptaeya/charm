#include "Entity.h"

namespace charm {

Entity::Entity()
{
}

Entity::~Entity()
{
    for (Component* component : m_components) {
        delete component;
    }
}

Entity::Entity(Entity&& other)
{
    m_components = std::move(other.m_components);
}

Entity& Entity::operator=(Entity&& other)
{
    if (this == &other)
        return *this;

    m_components = std::move(other.m_components);
    return *this;
}

}