#pragma once

#include "ui/elements/UIElement.h"
#include <string>
#include <utility>

namespace charm {

class UILabel : public UIElement {
    std::string m_text;
    float m_font_size = 24;

public:
    UILabel(const std::string&);
    ~UILabel() override;

    UILabel(const UILabel&) = delete;
    UILabel& operator=(const UILabel&) = delete;

    void draw(ImmediateUI& api) override;

private:
    std::pair<bool, int> calculate_overflow_index(const ImmediateUI& api) const;
};

}