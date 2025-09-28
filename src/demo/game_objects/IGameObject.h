#pragma once

#include "charm.h"

class IGameObject {
public:
    virtual ~IGameObject() = default;
    virtual void update(double delta_time) { }
    virtual void render(charm::Camera&, charm::Environment& environment) { }
    virtual void shadow(charm::Camera&) { }
};
