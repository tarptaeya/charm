#pragma once

#include "camera/Camera.h"
#include "ecs/Entity.h"
#include "objects/AbstractGameObject.h"

namespace charm {

class Renderer {
public:
    void render(Entity&, Camera&);
    void render(AbstractGameObject&, Camera&);
};

}