#pragma once

#include "Context.h"
#include "elements/Element.h"
#include <iostream>
#include <unordered_map>
#include <vector>

namespace charm {

class Application;

}

namespace charm::ui {

class Document {
    std::vector<Element*> m_children;
    std::unordered_map<std::string, Element*> m_id2element_cache;

    friend class charm::Application;
    Document() = default;

    void draw(float x, float y, float width, float height);

public:
    ~Document();

    Document(const Document&) = delete;
    Document& operator=(Document&) = delete;

    Document(Document&&);
    Document& operator=(Document&&);

    Element* get_element_by_id(const std::string& id);

    void add(Element*);
    void remove(Element*);
};

}