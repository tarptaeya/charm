#pragma once

namespace charm {

class Entity;

class Component {
    Entity& m_entity;

public:
    explicit Component(Entity&);
    virtual ~Component() = default;

    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;
};

}