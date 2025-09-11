#pragma once

#include "Style.h"
#include "memory/observer_ptr.h"
#include "ui/elements/Element.h"

namespace charm::ui {

class Panel {
    Style m_style;
    std::vector<ui::Element*> m_elements;
    charm::observer_ptr<ui::Element> m_root_element = nullptr;

public:
    Panel(const Style& style);
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
        element->set_style(m_style);
        m_elements.push_back(element);
        return charm::observer_ptr(element);
    }

    void set_root(charm::observer_ptr<ui::Element> root);
    void draw(float x, float y, float width, float height);

    void update(double delta_time);
    void on_char_callback(InputEventChar&);
    void on_key_callback(InputEventKey&);
    void on_cursor_pos_callback(InputEventMouseMotion&);
    void on_mouse_button_callback(InputEventMouseButton&);
    void on_scroll_callback(InputEventScroll&);
};

}