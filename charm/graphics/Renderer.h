#pragma once

#include "camera/Camera.h"
#include "ecs/Entity.h"

namespace charm {

class Renderer {
public:
    void render(Entity&, Camera&);
};

}