#pragma once

#include "ui/elements/Element.h"
#include "ui/elements/label/Label.h"
#include <functional>

namespace charm::ui {

class Button : public Element {
    Label m_label;
    std::function<void(InputEventMouseButton&)> m_on_click = [](InputEventMouseButton&) { };

public:
    Button(const std::string& text);
    ~Button();

    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    void set_bounds(float x, float y, float width, float height) override;

    Button& set_on_click_handler(std::function<void(InputEventMouseButton&)> on_click);
    Button& set_text(const std::string& text);

    void on_cursor_pos_callback(InputEventMouseMotion&) override;
    void on_mouse_button_callback(InputEventMouseButton&) override;

    void set_style(const Style&) override;
};

}