#pragma once

#include "InputEvent.h"

namespace charm {

class InputEventMouseButton : public InputEvent {
    int m_button = 0;
    int m_action = 0;
    int m_mods = 0;

public:
    InputEventMouseButton(int button, int action, int mods);

    int get_button() const;
    int get_action() const;
    int get_mods() const;
};

}