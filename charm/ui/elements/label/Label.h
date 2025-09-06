#pragma once

#include "ui/elements/Element.h"
#include <string>
#include <utility>

namespace charm::ui {

class Label : public Element {
    friend class TextInput;

    std::string m_text;
    float m_font_size = 14;

public:
    struct CharRect {
        float x = 0, y = 0, width = 0, height = 0;
        float u1 = 0, v1 = 0, u2 = 0, v2 = 0;
        float advance = 0;
    };

    Label(const std::string&);
    ~Label() override;

    Label(const Label&) = delete;
    Label& operator=(const Label&) = delete;

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    std::string get_text() const;
    void set_text(const std::string& text);

    int get_font_size() const;
    void set_font_size(int size);

    static CharRect get_rect_for_char(char c, float font_size);
};

}