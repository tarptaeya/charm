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

    m_immediate_ui.begin();
    m_immediate_ui.add_rect(x, y, width, height, { 0.9, 0.9, 0.9 }, 0, { 0, 0 }, { 0, 0 });

    float curr_y = y;
    for (const auto& child : m_children) {
        child->set_bounds(x, curr_y, width, child->get_min_height());
        curr_y += child->get_min_height();
        child->draw();
    }

    m_immediate_ui.commit();
}

}