#pragma once

#include "ui/elements/Element.h"

namespace charm::ui {

class PaddedContainer : public Element {
    float m_padding_left = 0;
    float m_padding_right = 0;
    float m_padding_top = 0;
    float m_padding_bottom = 0;
    std::vector<Element*> m_children;

public:
    PaddedContainer(float padding);
    PaddedContainer(float padding_left_right, float padding_top_bottom);
    PaddedContainer(float padding_left, float padding_right, float padding_top, float padding_bottom);

    ~PaddedContainer() override;

    PaddedContainer(const PaddedContainer&) = delete;
    PaddedContainer& operator=(const PaddedContainer&) = delete;

    void add(Element*);
    void remove(Element*);

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    void set_bounds(float x, float y, float width, float height) override;
};

}