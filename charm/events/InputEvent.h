#pragma once

namespace charm {

class InputEvent {
    bool m_should_stop_propagation = false;

public:
    InputEvent() = default;
    virtual ~InputEvent() = default;

    InputEvent(const InputEvent&) = delete;
    InputEvent& operator=(const InputEvent&) = delete;

    InputEvent(InputEvent&&) = default;
    InputEvent& operator=(InputEvent&&) = default;

    bool should_stop_propatation() const
    {
        return m_should_stop_propagation;
    }

    void stop_propagation()
    {
        m_should_stop_propagation = true;
    }
};

}