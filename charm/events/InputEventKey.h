#pragma once

#include "InputEvent.h"

namespace charm {

class InputEventKey : public InputEvent {
    int m_key = 0;
    int m_scancode = 0;
    int m_action = 0;
    int m_mods = 0;

public:
    InputEventKey(int key, int scancode, int action, int mods);

    int get_key() const;
    int get_scancode() const;
    int get_action() const;
    int get_mods() const;
};

}
