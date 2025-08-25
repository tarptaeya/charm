#pragma once

#include "ui/elements/Element.h"
#include <string>
#include <utility>

namespace charm::ui {

class Label : public Element {
    std::string m_text;
    float m_font_size = 24;

public:
    Label(ImmediateUI& context, const std::string&);
    ~Label() override;

    Label(const Label&) = delete;
    Label& operator=(const Label&) = delete;

    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;

private:
    std::pair<bool, int> calculate_overflow_index() const;
};

}