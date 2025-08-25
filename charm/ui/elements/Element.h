#pragma once

#include "ui/ImmediateUI.h"
#include <vector>

namespace charm::ui {

class Element {
public:
    virtual ~Element() { }

    virtual void draw(ImmediateUI& api) = 0;

    template <class T, typename... Args>
    void add(Args&&... args)
    {
        m_children.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

    float get_min_width() const;
    float get_min_height() const;
    bool get_is_width_expandable() const;
    bool get_is_height_expandable() const;

    float get_width() const;
    float get_height() const;
    void set_bounds(float x, float y, float width, float height);

protected:
    std::vector<std::unique_ptr<Element>> m_children;
    float m_min_width = 0;
    float m_min_height = 0;
    bool m_expand_width = false;
    bool m_expand_height = false;

    float m_x = 0;
    float m_y = 0;
    float m_width = 0;
    float m_height = 0;
};

}