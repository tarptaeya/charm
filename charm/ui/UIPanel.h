#pragma once

#include "FontMetadata.h"
#include "ImmediateUI.h"
#include <glad/gl.h>
#include <iostream>
#include <vector>

namespace charm {

class UIPanel {
    ImmediateUI m_immediate_ui;

public:
    UIPanel() = default;
    UIPanel(const FontMetadata& font_metadata);
    ~UIPanel();

    UIPanel(const UIPanel&) = delete;
    UIPanel& operator=(UIPanel&) = delete;

    UIPanel(UIPanel&&);
    UIPanel& operator=(UIPanel&&);

    void draw(int x, int y, int width, int height);
};

}