#pragma once

#include "ui/elements/Element.h"
#include "ui/elements/label/Label.h"

namespace charm::ui {

class Button : public Element {
    Label m_label;
    void (*m_on_click)() = nullptr;

public:
    Button(ImmediateUI& context, const std::string& text);
    ~Button();

    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;

    void draw() override;

    void set_bounds(float x, float y, float width, float height) override;

    void set_on_click_handler(void (*)());
};

}