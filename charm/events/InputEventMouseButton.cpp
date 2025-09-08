#include "InputEventMouseButton.h"

namespace charm {

InputEventMouseButton::InputEventMouseButton(int button, int action, int mods)
    : InputEvent()
    , m_button(button)
    , m_action(action)
    , m_mods(mods)
{
}

int InputEventMouseButton::get_button() const
{
    return m_button;
}

int InputEventMouseButton::get_action() const
{
    return m_action;
}

int InputEventMouseButton::get_mods() const
{
    return m_mods;
}

}