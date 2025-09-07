#pragma once

#include "ui/elements/Element.h"

namespace charm::ui {

class ScrollArea : public Element {
    Element* m_element = nullptr;
    float m_shift_x = 0;
    float m_shift_y = 0;

public:
    ScrollArea(Element* element);
    ~ScrollArea();

    ScrollArea(const ScrollArea&) = delete;
    ScrollArea& operator=(const ScrollArea&) = delete;

    void draw() override;
    void set_bounds(float x, float y, float width, float height) override;
    void set_clip(float x, float y, float width, float height) override;

    void on_mouse_button_callback(int button, int action, int mods) override;
};

}