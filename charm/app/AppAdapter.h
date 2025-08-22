#pragma once

namespace charm {

class AppAdapter {
public:
    virtual ~AppAdapter() = 0;
    virtual void update(double delta_time) = 0;
    virtual void on_key_input(int key, int scancode, int action, int mods) { }
    virtual void on_mouse_button(int button, int action, int mods) { }
};

}