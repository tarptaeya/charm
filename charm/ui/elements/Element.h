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

    virtual float get_min_width(const ImmediateUI& api) const;
    virtual float get_min_height(const ImmediateUI& api) const;
    virtual bool get_is_width_expandable(const ImmediateUI& api) const;
    virtual bool get_is_height_expandable(const ImmediateUI& api) const;

    float get_width() const;
    float get_height() const;
    virtual void set_bounds(float x, float y, float width, float height, const ImmediateUI& api);

protected:
    std::vector<std::unique_ptr<Element>> m_children;

    float m_x = 0;
    float m_y = 0;
    float m_width = 0;
    float m_height = 0;
};

}