#include "Document.h"

namespace charm::ui {

Document::Document(const FontMetadata& font_metadata)
    : m_immediate_ui(font_metadata)
{
}

Document::~Document()
{
}

Document::Document(Document&& other)
    : m_immediate_ui(std::move(other.m_immediate_ui))
{
}

Document& Document::operator=(Document&& other)
{
    if (this == &other)
        return *this;

    m_immediate_ui = std::move(other.m_immediate_ui);

    return *this;
}

void Document::draw(int x, int y, int width, int height)
{

    m_immediate_ui.begin(x, y, width, height);
    m_immediate_ui.add_rect(x, y, width, height, { 0.9, 0.9, 0.9 }, 0, { 0, 0 }, { 0, 0 });

    int element_height = height / m_children.size();
    int curr_y = y;
    for (const auto& child : m_children) {
        child->set_bounds(x, curr_y, width, height, m_immediate_ui);
        curr_y += element_height;
        child->draw(m_immediate_ui);
    }

    m_immediate_ui.commit();
}

}