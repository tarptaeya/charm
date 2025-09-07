#pragma once

#include "ui/Context.h"

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
    void set_clip(float x, float y, float width, float height);
    void add_clip(float x, float y, float width, float height);

    virtual void update(double delta_time) { }

    virtual void on_mouse_enter() { }
    virtual void on_mouse_exit() { }

    virtual void on_char_callback(unsigned int codepoint) { }
    virtual void on_key_callback(int key, int scancode, int action, int mods) { }
    virtual void on_cursor_pos_callback(double x, double y);
    virtual void on_mouse_button_callback(int button, int action, int mods);

protected:
    float m_x = 0;
    float m_y = 0;
    float m_width = 0;
    float m_height = 0;

    float m_clip_x = 0;
    float m_clip_y = 0;
    float m_clip_width = 0;
    float m_clip_height = 0;

    float m_mouse_x = 0;
    float m_mouse_y = 0;

    bool m_is_mouse_hover = false;
    bool m_is_mouse_pressed = false;
    bool m_is_mouse_just_pressed = false;
};

}