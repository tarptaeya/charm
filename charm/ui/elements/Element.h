#pragma once

#include "ui/ImmediateUI.h"
#include <vector>

namespace charm::ui {

class Element {

public:
    Element(ImmediateUI& context);
    virtual ~Element() { }

    std::string get_id() const;
    void set_id(const std::string& id);

    virtual void draw();

    template <typename T>
    T* get_element_by_id(const std::string& id)
    {
        if (m_id == id)
            return dynamic_cast<T*>(this);

        for (const auto& child : m_children) {
            auto ans = child->get_element_by_id<T>(id);
            if (ans)
                return ans;
        }
        return nullptr;
    }

    template <class T, typename... Args>
    T& add(Args&&... args)
    {
        m_children.push_back(std::make_unique<T>(m_context, std::forward<Args>(args)...));
        return dynamic_cast<T&>(*m_children.back());
    }

    virtual float get_min_width() const;
    virtual float get_min_height() const;
    virtual bool get_is_width_expandable() const;
    virtual bool get_is_height_expandable() const;

    float get_width() const;
    float get_height() const;
    virtual void set_bounds(float x, float y, float width, float height);

    virtual void on_mouse_enter() { }
    virtual void on_mouse_exit() { }

protected:
    std::string m_id;
    ImmediateUI& m_context;
    std::vector<std::unique_ptr<Element>> m_children;

    float m_x = 0;
    float m_y = 0;
    float m_width = 0;
    float m_height = 0;

    bool m_is_mouse_hover = false;
    bool m_is_mouse_pressed = false;
    bool m_is_mouse_just_pressed = false;
};

}