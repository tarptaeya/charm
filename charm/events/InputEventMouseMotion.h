#pragma once

#include "InputEvent.h"

namespace charm {

class InputEventMouseMotion : public InputEvent {
    double m_x = 0;
    double m_y = 0;

public:
    InputEventMouseMotion(double x, double y);

    double get_x() const;
    double get_y() const;
};

}
