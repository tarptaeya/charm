#pragma once

#include "ui/elements/Element.h"
#include <string>
#include <utility>

namespace charm::ui {

class Label : public Element {
    std::string m_text;
    float m_font_size = 14;

public:
    Label(ImmediateUI& context, const std::string&);
    ~Label() override;

    Label(const Label&) = delete;
    Label& operator=(const Label&) = delete;

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

    std::string get_text() const;
    void set_text(const std::string& text);
    void set_font_size(int size);

private:
    std::pair<bool, int> calculate_overflow_index() const;
};

}