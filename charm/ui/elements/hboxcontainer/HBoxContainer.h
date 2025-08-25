#pragma once

#include "ui/elements/Element.h"

namespace charm::ui {

class HBoxContainer : public Element {
public:
    HBoxContainer(ImmediateUI& context);
    ~HBoxContainer() override;

    HBoxContainer(const HBoxContainer&) = delete;
    HBoxContainer& operator=(const HBoxContainer&) = delete;

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;
    bool get_is_width_expandable() const override;
    bool get_is_height_expandable() const override;

    void set_bounds(float x, float y, float width, float height) override;
};

}