#pragma once

#include "ui/elements/Element.h"

namespace charm {

class Font;

class AppAdapter {
    friend class Application;

public:
    AppAdapter() = default;
    virtual ~AppAdapter() { }

    AppAdapter(const AppAdapter&) = delete;
    AppAdapter& operator=(const AppAdapter&) = delete;

    virtual void update(double delta_time) = 0;

    void add(ui::Element*);
    void remove(ui::Element*);

private:
    void draw(Font&, gl::Program&);

protected:
    std::vector<ui::Element*> m_children;
};

}