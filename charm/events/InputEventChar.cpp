#include "InputEventChar.h"

namespace charm {

InputEventChar::InputEventChar(unsigned int codepoint)
    : InputEvent()
    , m_codepoint(codepoint)
{
}

unsigned int InputEventChar::get_codepoint() const
{
    return m_codepoint;
}

}