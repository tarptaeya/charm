#pragma once

#include "InputEvent.h"

namespace charm {

class InputEventScroll : public InputEvent {
    double m_xoffset = 0;
    double m_yoffset = 0;

public:
    InputEventScroll(double xoffset, double yoffset);

    double get_xoffset() const;
    double get_yoffset() const;
};

}