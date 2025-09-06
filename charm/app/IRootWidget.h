#pragma once

#include "ui/elements/Element.h"

namespace charm {

class IRootWidget {
    friend class Application;

public:
    IRootWidget() = default;
    virtual ~IRootWidget() { }

    IRootWidget(const IRootWidget&) = delete;
    IRootWidget& operator=(const IRootWidget&) = delete;

    void draw(ui::Element* element, float x, float y, float width, float height);

    virtual void update(double delta_time) = 0;
    virtual void on_char_callback(unsigned int codepoint) { }
    virtual void on_key_callback(int key, int scancode, int action, int mods) { }

protected:
    std::vector<ui::Element*> m_children;
};

}