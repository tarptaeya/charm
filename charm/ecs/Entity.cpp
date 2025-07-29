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

}