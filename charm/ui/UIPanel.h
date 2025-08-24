#pragma once

#include "FontMetadata.h"
#include "ImmediateUI.h"
#include "elements/UIElement.h"
#include <glad/gl.h>
#include <iostream>
#include <vector>

namespace charm {

class UIPanel {
    ImmediateUI m_immediate_ui;
    std::vector<std::unique_ptr<UIElement>> m_children;

public:
    UIPanel() = default;
    UIPanel(const FontMetadata& font_metadata);
    ~UIPanel();

    UIPanel(const UIPanel&) = delete;
    UIPanel& operator=(UIPanel&) = delete;

    UIPanel(UIPanel&&);
    UIPanel& operator=(UIPanel&&);

    template <class T, typename... Args>
    T& add(Args&&... args)
    {
        static_assert(std::is_base_of<UIElement, T>::value, "only objects derived from UIElement can be added as child of UIPanel");
        m_children.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return dynamic_cast<T&>(*m_children.back());
    }

    void draw(int x, int y, int width, int height);
};

}