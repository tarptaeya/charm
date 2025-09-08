#include "InputEventKey.h"

namespace charm {

InputEventKey::InputEventKey(int key, int scancode, int action, int mods)
    : InputEvent()
    , m_key(key)
    , m_scancode(scancode)
    , m_action(action)
    , m_mods(mods)
{
}

int InputEventKey::get_key() const
{
    return m_key;
}

int InputEventKey::get_scancode() const
{
    return m_scancode;
}

int InputEventKey::get_action() const
{
    return m_action;
}

int InputEventKey::get_mods() const
{
    return m_mods;
}

}