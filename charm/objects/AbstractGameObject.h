#pragma once

#include "camera/Camera.h"

namespace charm {

class AbstractGameObject {
public:
    virtual ~AbstractGameObject() = default;
    virtual void update(double delta_time) { }
    virtual void render(Camera&) { }
    virtual void on_key_input(int key, int scancode, int action, int mods) { }
    virtual void on_mouse_button(int button, int action, int mods) { }
};

}