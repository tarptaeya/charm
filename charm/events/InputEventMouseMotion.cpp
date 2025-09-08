#include "InputEventMouseMotion.h"

namespace charm {

InputEventMouseMotion::InputEventMouseMotion(double x, double y)
    : InputEvent()
    , m_x(x)
    , m_y(y)
{
}

double InputEventMouseMotion::get_x() const
{
    return m_x;
}

double InputEventMouseMotion::get_y() const
{
    return m_y;
}

}