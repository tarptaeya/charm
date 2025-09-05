#pragma once

#include "ui/elements/Element.h"

namespace charm {

class Font;

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

private:
    void draw(Font&, gl::Program&);

protected:
    std::vector<ui::Element*> m_children;
};

}