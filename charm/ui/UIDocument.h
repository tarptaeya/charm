#pragma once

#include "FontMetadata.h"
#include "ImmediateUI.h"
#include "elements/UIElement.h"
#include <glad/gl.h>
#include <iostream>
#include <vector>

namespace charm {

class UIDocument {
    ImmediateUI m_immediate_ui;
    std::vector<std::unique_ptr<UIElement>> m_children;

public:
    UIDocument() = default;
    UIDocument(const FontMetadata& font_metadata);
    ~UIDocument();

    UIDocument(const UIDocument&) = delete;
    UIDocument& operator=(UIDocument&) = delete;

    UIDocument(UIDocument&&);
    UIDocument& operator=(UIDocument&&);

    template <class T, typename... Args>
    T& add(Args&&... args)
    {
        static_assert(std::is_base_of<UIElement, T>::value, "only objects derived from UIElement can be added as child of UIDocument");
        m_children.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return dynamic_cast<T&>(*m_children.back());
    }

    void draw(int x, int y, int width, int height);
};

}