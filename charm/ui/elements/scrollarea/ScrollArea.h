#pragma once

#include "memory/observer_ptr.h"
#include "ui/elements/Element.h"

namespace charm::ui {

class ScrollArea : public Element {
    charm::observer_ptr<Element> m_element = nullptr;
    float m_shift_x = 0;
    float m_shift_y = 0;

public:
    ScrollArea(const charm::observer_ptr<Element>&);
    ~ScrollArea();

    ScrollArea(const ScrollArea&) = delete;
    ScrollArea& operator=(const ScrollArea&) = delete;

    void draw() override;
    void set_bounds(float x, float y, float width, float height) override;

    float get_min_width() const override;
    float get_min_height() const override;

    void on_char_callback(InputEventChar&) override;
    void on_key_callback(InputEventKey&) override;
    void on_cursor_pos_callback(InputEventMouseMotion&) override;
    void on_mouse_button_callback(InputEventMouseButton&) override;
    void on_scroll_callback(InputEventScroll&) override;

private:
    bool get_is_mouse_hover_left_button();
    bool get_is_mouse_hover_right_button();
    bool get_is_mouse_hover_top_button();
    bool get_is_mouse_hover_bottom_button();
};

}