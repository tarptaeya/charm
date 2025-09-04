#pragma once

#include "ui/elements/Element.h"

namespace charm::ui {

class VBoxContainer : public Element {
public:
    VBoxContainer();
    ~VBoxContainer() override;

    VBoxContainer(const VBoxContainer&) = delete;
    VBoxContainer& operator=(const VBoxContainer&) = delete;

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    void set_bounds(float x, float y, float width, float height) override;
};

}