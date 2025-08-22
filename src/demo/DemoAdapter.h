#pragma once

#include "charm.h"

class DemoAdapter : public charm::AppAdapter {
public:
    DemoAdapter();
    ~DemoAdapter() override;

    void update(double delta_time) override;

    void on_key_input(int key, int scancode, int action, int mods) override;
    void on_mouse_button(int button, int action, int mods) override;
};