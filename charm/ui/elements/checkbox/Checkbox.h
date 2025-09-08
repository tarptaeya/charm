#pragma once

#include "ui/elements/Element.h"
#include "ui/elements/label/Label.h"
#include <functional>

namespace charm::ui {

class Checkbox : public Element {
    bool m_value = false;
    Label m_label;

public:
    Checkbox(const std::string& text);
    ~Checkbox();

    Checkbox(const Checkbox&) = delete;
    Checkbox& operator=(const Checkbox&) = delete;

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    void set_bounds(float x, float y, float width, float height) override;

    Checkbox& set_text(const std::string& text);

    void on_mouse_enter() override;
    void on_mouse_exit() override;

    bool is_checked() const;

    void on_cursor_pos_callback(const InputEventMouseMotion&) override;
    void on_mouse_button_callback(const InputEventMouseButton&) override;

private:
    int get_box_size() const;
};

}