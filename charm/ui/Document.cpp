#include "Document.h"
#include "charm.h"

namespace charm::ui {

Document::~Document()
{
}

Document::Document(Document&& other)
{
}

Document& Document::operator=(Document&& other)
{
    if (this == &other)
        return *this;

    return *this;
}

void Document::draw(int x, int y, int width, int height)
{

    m_immediate_ui.begin(x, y, width, height);
    m_immediate_ui.add_rect(x, y, width, height, { 0.9, 0.9, 0.9 }, 0, { 0, 0 }, { 0, 0 });

    float element_height = height * 1.0f / m_children.size();
    float curr_y = y;
    for (const auto& child : m_children) {
        child->set_bounds(x, curr_y, width, element_height);
        curr_y += element_height;
        child->draw();
    }

    m_immediate_ui.commit();
}

}