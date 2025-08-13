#pragma once

#include "Entity.h"
#include "camera/Camera.h"

namespace charm {

class Renderer {
public:
    void render(Entity&, Camera&);
};

}