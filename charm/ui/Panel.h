#pragma once

#include "memory/observer_ptr.h"
#include "ui/elements/Element.h"

namespace charm::ui {

class Panel {
    std::vector<ui::Element*> m_elements;
    charm::observer_ptr<ui::Element> m_root_element = nullptr;

public:
    Panel() = default;
    ~Panel();

    Panel(const Panel&) = delete;
    Panel& operator=(const Panel&) = delete;

    Panel(Panel&&);
    Panel& operator=(Panel&&);

    template <class T, typename... Args>
    charm::observer_ptr<T> create(Args&&... args)
    {
        static_assert(std::is_base_of<Element, T>::value);
        T* element = new T(std::forward<Args>(args)...);
        m_elements.push_back(element);
        return charm::observer_ptr(element);
    }

    void set_root(charm::observer_ptr<ui::Element> root);
    void draw(float x, float y, float width, float height);
};

}