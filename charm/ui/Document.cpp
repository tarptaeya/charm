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

void Document::draw(float x, float y, float width, float height)
{

    auto& ui_context = Context::get_instance();
    ui_context.begin();
    ui_context.add_rect(x, y, width, height, { 0.9, 0.9, 0.9 }, 0, { 0, 0 }, { 0, 0 });

    float curr_y = y;
    for (const auto& child : m_children) {
        float child_width = child->get_min_width();
        if (child->get_is_width_expandable()) {
            child_width = width;
        }
        child->set_bounds(x, curr_y, child_width, child->get_min_height());
        curr_y += child->get_min_height();
        child->draw();
    }

    ui_context.commit();
}

Element* Document::get_element_by_id(const std::string& id)
{
    if (m_id2element_cache.count(id)) {
        return m_id2element_cache[id];
    }

    for (const auto& child : m_children) {
        Element* ans = child->get_element_by_id(id);
        if (ans) {
            m_id2element_cache[id] = ans;
            return ans;
        }
    }
    return nullptr;
}

}