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

    virtual void update(double delta_time) = 0;

    void add(ui::Element*);
    void remove(ui::Element*);

    virtual void on_key_callback(int key, int scancode, int action, int mods) { }

private:
    void draw();

protected:
    std::vector<ui::Element*> m_children;
};

}