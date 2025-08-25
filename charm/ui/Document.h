#pragma once

#include "FontMetadata.h"
#include "ImmediateUI.h"
#include "elements/Element.h"
#include <glad/gl.h>
#include <iostream>
#include <vector>

namespace charm::ui {

class Document {
    ImmediateUI m_immediate_ui;
    std::vector<std::unique_ptr<Element>> m_children;

public:
    Document() = default;
    Document(const FontMetadata& font_metadata);
    ~Document();

    Document(const Document&) = delete;
    Document& operator=(Document&) = delete;

    Document(Document&&);
    Document& operator=(Document&&);

    template <class T, typename... Args>
    T& add(Args&&... args)
    {
        static_assert(std::is_base_of<Element, T>::value, "only objects derived from Element can be added as child of Document");
        m_children.push_back(std::make_unique<T>(m_immediate_ui, std::forward<Args>(args)...));
        return dynamic_cast<T&>(*m_children.back());
    }

    void draw(int x, int y, int width, int height);
};

}