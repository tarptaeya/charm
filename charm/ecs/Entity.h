#pragma once

#include "Component.h"
#include <iostream>
#include <vector>

namespace charm {

class Entity {
    std::vector<Component*> m_components;

public:
    explicit Entity();
    ~Entity();

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    template <typename T, typename... Args>
    T* add_component(Args&&... args)
    {
        static_assert(std::is_base_of<Component, T>::value, "cannot add non component to the entity");

        T* component = new T(this, std::forward<Args>(args)...);
        m_components.push_back(component);
        return component;
    }

    template <typename T>
    T* get_component() const
    {
        for (Component* component : m_components) {
            T* ans = dynamic_cast<T*>(component);
            if (ans)
                return ans;
        }
#ifdef DEBUG_BUILD
        std::cout << "[debug] unable to get component" << std::endl;
#endif
        return nullptr;
    }
};

}