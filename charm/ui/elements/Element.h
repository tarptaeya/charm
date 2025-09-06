#pragma once

#include "ui/Context.h"
#include <vector>

namespace charm::ui {

class Element {
    bool m_is_width_expandable = false;
    bool m_is_height_expandable = false;

public:
    Element();
    virtual ~Element() { }

    Element(const Element&) = delete;
    Element& operator=(const Element&) = delete;

    Element(Element&&);
    Element& operator=(Element&&);

    std::string get_id() const;
    Element& set_id(const std::string& id);
    Element* get_element_by_id(const std::string& id);
    void add(Element*);
    void remove(Element*);

    virtual void draw();

    virtual float get_min_width() const;
    virtual float get_min_height() const;

    bool get_is_width_expandable() const;
    Element& set_is_width_expandable(bool);
    bool get_is_height_expandable() const;
    Element& set_is_height_expandable(bool);

    float get_width() const;
    float get_height() const;
    virtual void set_bounds(float x, float y, float width, float height);

    virtual void update(double delta_time) { }

    virtual void on_mouse_enter() { }
    virtual void on_mouse_exit() { }

    virtual void on_char_callback(unsigned int codepoint) { }
    virtual void on_key_callback(int key, int scancode, int action, int mods) { }

protected:
    std::string m_id;
    std::vector<Element*> m_children;

    float m_x = 0;
    float m_y = 0;
    float m_width = 0;
    float m_height = 0;

    bool m_is_mouse_hover = false;
    bool m_is_mouse_pressed = false;
    bool m_is_mouse_just_pressed = false;
};

}