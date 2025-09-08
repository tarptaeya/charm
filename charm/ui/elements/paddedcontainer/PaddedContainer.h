#pragma once

#include "memory/observer_ptr.h"
#include "ui/elements/Element.h"

namespace charm::ui {

class PaddedContainer : public Element {
    float m_padding_left = 0;
    float m_padding_right = 0;
    float m_padding_top = 0;
    float m_padding_bottom = 0;
    charm::observer_ptr<Element> m_element = nullptr;

public:
    PaddedContainer(const charm::observer_ptr<Element>&, float padding);
    PaddedContainer(const charm::observer_ptr<Element>&, float padding_left_right, float padding_top_bottom);
    PaddedContainer(const charm::observer_ptr<Element>&, float padding_left, float padding_right, float padding_top, float padding_bottom);

    ~PaddedContainer() override;

    PaddedContainer(const PaddedContainer&) = delete;
    PaddedContainer& operator=(const PaddedContainer&) = delete;

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    void set_bounds(float x, float y, float width, float height) override;

    void on_char_callback(InputEventChar&) override;
    void on_key_callback(InputEventKey&) override;
    void on_cursor_pos_callback(InputEventMouseMotion&) override;
    void on_mouse_button_callback(InputEventMouseButton&) override;
};

}