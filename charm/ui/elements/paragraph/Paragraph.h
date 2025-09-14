#pragma once

#include "ui/elements/Element.h"
#include "ui/elements/label/Label.h"

namespace charm::ui {

class Paragraph : public Element {
    std::string m_text;
    float m_font_size = 14;
    std::vector<std::vector<std::string>> m_layout;
    float m_cached_layout_width = 0;

public:
    Paragraph(const std::string&);
    ~Paragraph() override;

    Paragraph(const Paragraph&) = delete;
    Paragraph& operator=(const Paragraph&) = delete;

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    std::string get_text() const;
    void set_text(const std::string& text);

    int get_font_size() const;
    void set_font_size(int size);

private:
    void build_layout();
};

}