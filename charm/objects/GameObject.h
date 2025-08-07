#pragma once

#include "camera/Camera.h"

namespace charm {

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void render(Camera&) = 0;
};

}