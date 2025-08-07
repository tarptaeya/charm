#pragma once

#include "camera/Camera.h"

namespace charm {

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void update(double delta_time) { }
    virtual void render(Camera&) { }
};

}