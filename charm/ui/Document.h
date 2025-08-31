#pragma once

#include "Context.h"
#include "elements/Element.h"
#include <glad/gl.h>
#include <iostream>
#include <vector>

namespace charm {

class Application;

}

namespace charm::ui {

class Document {
    Context m_immediate_ui;
    std::vector<std::unique_ptr<Element>> m_children;

    friend class charm::Application;
    Document() = default;

    void draw(float x, float y, float width, float height);

public:
    ~Document();

    Document(const Document&) = delete;
    Document& operator=(Document&) = delete;

    Document(Document&&);
    Document& operator=(Document&&);

    template <typename T>
    T* get_element_by_id(const std::string& id)
    {
        for (const auto& child : m_children) {
            Element* ans = child->get_element_by_id(id);
            if (ans)
                return dynamic_cast<T*>(ans);
        }
        return nullptr;
    }

    template <class T, typename... Args>
    T& add(Args&&... args)
    {
        static_assert(std::is_base_of<Element, T>::value, "only objects derived from Element can be added as child of Document");
        m_children.push_back(std::make_unique<T>(m_immediate_ui, std::forward<Args>(args)...));
        return dynamic_cast<T&>(*m_children.back());
    }
};

}