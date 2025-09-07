#pragma once

#include "memory/observer_ptr.h"
#include "ui/elements/Element.h"
#include <vector>

namespace charm::ui {

class HBoxContainer : public Element {
    std::vector<charm::observer_ptr<Element>> m_children;

public:
    HBoxContainer();
    ~HBoxContainer() override;

    HBoxContainer(const HBoxContainer&) = delete;
    HBoxContainer& operator=(const HBoxContainer&) = delete;

    void add(const charm::observer_ptr<Element>&);
    void remove(const charm::observer_ptr<Element>&);

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    void set_bounds(float x, float y, float width, float height) override;
};

}