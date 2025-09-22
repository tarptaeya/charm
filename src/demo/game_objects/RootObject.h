#pragma once

#include "IGameObject.h"
#include "TestObject.h"
#include <vector>

class RootObject : public IGameObject {
    std::vector<std::unique_ptr<IGameObject>> m_objects;
    std::unique_ptr<IGameObject> m_ground = nullptr;

public:
    RootObject();

    ~RootObject() = default;

    void update(double delta_time) override;
    void render(charm::Camera& camera) override;

    template <typename T, typename... Args>
    void add_object(Args&&... args)
    {
        auto object = std::make_unique<T>(std::forward<Args>(args)...);
        m_objects.push_back(std::move(object));
    }
};
