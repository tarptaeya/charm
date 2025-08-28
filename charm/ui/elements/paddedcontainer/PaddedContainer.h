#pragma once

#include "ui/elements/Element.h"

namespace charm::ui {

class PaddedContainer : public Element {
    float m_padding_left = 0;
    float m_padding_right = 0;
    float m_padding_top = 0;
    float m_padding_bottom = 0;

public:
    PaddedContainer(ImmediateUI& context, float padding);
    PaddedContainer(ImmediateUI& context, float padding_left_right, float padding_top_bottom);
    PaddedContainer(ImmediateUI& context, float padding_left, float padding_right, float padding_top, float padding_bottom);

    ~PaddedContainer() override;

    PaddedContainer(const PaddedContainer&) = delete;
    PaddedContainer& operator=(const PaddedContainer&) = delete;

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;
    bool get_is_width_expandable() const override;
    bool get_is_height_expandable() const override;

    void set_bounds(float x, float y, float width, float height) override;
};

}