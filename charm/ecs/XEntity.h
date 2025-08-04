#pragma once

#include "XComponent.h"
#include <iostream>
#include <vector>

class XEntity {
    std::vector<XComponent*> m_components;

public:
    explicit XEntity();
    ~XEntity();

    XEntity(const XEntity&) = delete;
    XEntity& operator=(const XEntity&) = delete;

    XEntity(XEntity&&);
    XEntity& operator=(XEntity&&);

    template <typename T, typename... Args>
    T* add_component(Args&&... args)
    {
        static_assert(std::is_base_of<XComponent, T>::value, "cannot add non component to the entity");

        T* component = new T(*this, std::forward<Args>(args)...);
        m_components.push_back(component);
        return component;
    }

    template <typename T>
    T* get_component() const
    {
        for (XComponent* component : m_components) {
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
