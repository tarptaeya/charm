#pragma once

#include "ui/elements/Element.h"
#include <vector>

namespace charm::ui {

class VBoxContainer : public Element {
    std::vector<Element*> m_children;

public:
    VBoxContainer();
    ~VBoxContainer() override;

    VBoxContainer(const VBoxContainer&) = delete;
    VBoxContainer& operator=(const VBoxContainer&) = delete;

    void add(Element*);
    void remove(Element*);

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    void set_bounds(float x, float y, float width, float height) override;
};

}