#pragma once

#include "ui/elements/label/Label.h"

namespace charm::ui {

class TextInput : public Element {
    std::string m_value;
    int m_cursor_pos = 0;
    bool m_show_cursor = false;
    double m_cursor_time_so_far = 0;
    Label m_label;

public:
    TextInput();
    ~TextInput();

    TextInput(const TextInput&) = delete;
    TextInput& operator=(const TextInput&) = delete;

    std::string get_value() const;
    void set_value(const std::string&);

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    void set_bounds(float x, float y, float width, float height) override;

    void update(double delta_time) override;

    void on_mouse_enter() override;
    void on_mouse_exit() override;

    void on_key_callback(int key, int scancode, int action, int mods) override;
};

}