#include "UIPanel.h"

namespace charm {

UIPanel::UIPanel(const FontMetadata& font_metadata)
    : m_immediate_ui(font_metadata)
{
}

UIPanel::~UIPanel()
{
}

UIPanel::UIPanel(UIPanel&& other)
    : m_immediate_ui(std::move(other.m_immediate_ui))
{
}

UIPanel& UIPanel::operator=(UIPanel&& other)
{
    if (this == &other)
        return *this;

    m_immediate_ui = std::move(other.m_immediate_ui);

    return *this;
}

void UIPanel::draw(int x, int y, int width, int height)
{

    m_immediate_ui.begin(x, y, width, height);
    m_immediate_ui.add_rect(x, y, width, height, { 0.9, 0.9, 0.9 }, 0, { 0, 0 }, { 0, 0 });

    for (const auto& child : m_children) {
        child->draw(x, y, width, height, m_immediate_ui);
    }

    m_immediate_ui.commit();
}

}