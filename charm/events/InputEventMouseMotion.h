#pragma once

#include "InputEvent.h"

namespace charm {

class InputEventMouseMotion : public InputEvent {
    double m_x = 0;
    double m_y = 0;
    int m_cursor_shape = 0;

public:
    InputEventMouseMotion(double x, double y);

    double get_x() const;
    double get_y() const;
    int get_cursor_shape() const;
    void set_cursor_shape(int cursor_shape);
};

}
