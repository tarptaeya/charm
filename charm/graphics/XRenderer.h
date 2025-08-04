#pragma once

#include "camera/XCamera.h"
#include "ecs/XEntity.h"

class XRenderer {
public:
    void render(XEntity&, XCamera&);
};
