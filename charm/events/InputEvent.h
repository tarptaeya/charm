#pragma once

namespace charm {

class InputEvent {
    bool m_is_handled = false;

public:
    InputEvent() = default;
    virtual ~InputEvent() = default;

    InputEvent(const InputEvent&) = delete;
    InputEvent& operator=(const InputEvent&) = delete;

    InputEvent(InputEvent&&) = default;
    InputEvent& operator=(InputEvent&&) = default;

    bool is_handled() const
    {
        return m_is_handled;
    }

    void stop_propagation()
    {
        m_is_handled = true;
    }
};

}