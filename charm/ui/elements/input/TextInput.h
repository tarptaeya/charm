#pragma once

#include "ui/elements/Element.h"

namespace charm::ui {

class TextInput : public Element {
    std::string m_value;
    int m_cursor_pos = 0;
    float m_font_size = 14;

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

    int get_font_size() const;
    void set_font_size(int size);

    void update(double delta_time) override;

    void on_mouse_enter() override;
    void on_mouse_exit() override;

    void on_key_callback(int key, int scancode, int action, int mods) override;
};

}