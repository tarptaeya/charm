#pragma once

#include "events/InputEventChar.h"
#include "events/InputEventKey.h"
#include "events/InputEventMouseButton.h"
#include "events/InputEventMouseMotion.h"
#include "events/InputEventScroll.h"

namespace charm {

class AppAdapter {
    friend class Application;

public:
    AppAdapter() = default;
    virtual ~AppAdapter() { }

    AppAdapter(const AppAdapter&) = delete;
    AppAdapter& operator=(const AppAdapter&) = delete;

    virtual void update(double delta_time) = 0;
    virtual void on_char_callback(InputEventChar&) { }
    virtual void on_key_callback(InputEventKey&) { }
    virtual void on_cursor_position_callback(InputEventMouseMotion&) { }
    virtual void on_mouse_button_callback(InputEventMouseButton&) { }
    virtual void on_scroll_callback(InputEventScroll&) { }
};

}