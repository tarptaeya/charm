#include "InputEventScroll.h"

namespace charm {

InputEventScroll::InputEventScroll(double xoffset, double yoffset)
    : m_xoffset(xoffset)
    , m_yoffset(yoffset)
{
}

double InputEventScroll::get_xoffset() const
{
    return m_xoffset;
}

double InputEventScroll::get_yoffset() const
{
    return m_yoffset;
}

}