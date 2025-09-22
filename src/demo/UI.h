#pragma once

#include "charm.h"

using namespace charm;

class UI {
    ui::Style m_style;
    std::unique_ptr<ui::Panel> m_panel = nullptr;
    observer_ptr<ui::Label> m_fps_counter = nullptr;

public:
    UI();
    ~UI() = default;

    UI(const UI&) = delete;
    UI& operator=(const UI&) = delete;

    void update(double delta_time);
    void draw(float x, float y, float width, float height);

    void on_char_callback(InputEventChar&);
    void on_key_callback(InputEventKey&);
    void on_cursor_pos_callback(InputEventMouseMotion&);
    void on_mouse_button_callback(InputEventMouseButton&);
    void on_scroll_callback(InputEventScroll&);
};