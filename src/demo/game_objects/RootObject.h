#pragma once

#include "IGameObject.h"
#include "TestObject.h"
#include <vector>

using charm::Matrix4f;

class RootObject : public IGameObject {
    std::vector<std::unique_ptr<IGameObject>> m_objects;

public:
    RootObject();

    ~RootObject() = default;

    void render(charm::Camera& camera) override;

    template <typename T, typename... Args>
    void add_object(Args&&... args)
    {
        auto object = std::make_unique<T>(std::forward<Args>(args)...);
        m_objects.push_back(std::move(object));
    }
};
