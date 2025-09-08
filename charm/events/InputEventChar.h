#pragma once

#include "InputEvent.h"

namespace charm {

class InputEventChar : public InputEvent {
    unsigned int m_codepoint = 0;

public:
    InputEventChar(unsigned int codepoint);

    unsigned int get_codepoint() const;
};

}
