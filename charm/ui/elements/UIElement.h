#pragma once

#include "ui/ImmediateUI.h"
#include <vector>

namespace charm {

class UIElement {
public:
    virtual ~UIElement() { }

    virtual void draw(int x, int y, int width, int height, ImmediateUI& api) = 0;

    template <class T, typename... Args>
    void add(Args&&... args)
    {
        m_children.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

protected:
    std::vector<std::unique_ptr<UIElement>> m_children;
};

}