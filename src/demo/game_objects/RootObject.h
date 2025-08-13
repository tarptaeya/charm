#pragma once

#include "IGameObject.h"
#include <vector>

class RootObject : public IGameObject {
    std::vector<std::unique_ptr<IGameObject>> m_objects;

public:
    ~RootObject() = default;

    void render(charm::Camera& camera) override
    {
        for (auto& object : m_objects) {
            object->render(camera);
        }
    }

    template <typename T, typename... Args>
    void add_object(Args&&... args)
    {
        auto object = std::make_unique<T>(std::forward<Args>(args)...);
        m_objects.push_back(std::move(object));
    }
};
