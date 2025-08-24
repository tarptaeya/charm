#pragma once

#include "ui/elements/UIElement.h"
#include <string>

namespace charm {

class UILabel : public UIElement {
    std::string m_text;

public:
    UILabel(const std::string&);
    ~UILabel() override;

    UILabel(const UILabel&) = delete;
    UILabel& operator=(const UILabel&) = delete;

    void draw(int x, int y, int width, int height, ImmediateUI& api) override;
};

}