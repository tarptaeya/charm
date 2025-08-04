#pragma once

#include "ecs/Entity.h"

namespace charm {

class Renderer {
public:
    void render(Entity& entity);
};

}