#pragma once

#include "memory/observer_ptr.h"
#include "ui/elements/Element.h"
#include <vector>

namespace charm::ui {

class VBoxContainer : public Element {
    std::vector<charm::observer_ptr<Element>> m_children;

public:
    VBoxContainer();
    ~VBoxContainer() override;

    VBoxContainer(const VBoxContainer&) = delete;
    VBoxContainer& operator=(const VBoxContainer&) = delete;

    void add(const charm::observer_ptr<Element>&);
    void remove(const charm::observer_ptr<Element>&);

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    void set_bounds(float x, float y, float width, float height) override;

    void on_cursor_pos_callback(const InputEventMouseMotion& event) override;
};

}