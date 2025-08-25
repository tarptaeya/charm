#pragma once

#include "ui/elements/Element.h"

namespace charm::ui {

class HBoxContainer : public Element {
public:
    HBoxContainer() = default;
    ~HBoxContainer() override;

    HBoxContainer(const HBoxContainer&) = delete;
    HBoxContainer& operator=(const HBoxContainer&) = delete;

    void draw(ImmediateUI& api) override;

    float get_min_width(const ImmediateUI& api) const override;
    float get_min_height(const ImmediateUI& api) const override;
    bool get_is_width_expandable(const ImmediateUI& api) const override;
    bool get_is_height_expandable(const ImmediateUI& api) const override;

    void set_bounds(float x, float y, float width, float height, const ImmediateUI& api) override;
};

}