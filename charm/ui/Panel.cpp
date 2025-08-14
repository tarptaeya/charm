#include "Panel.h"

namespace charm {

Panel::Panel()
{
}

Panel::~Panel()
{
    for (IElement* element : m_children)
        delete element;
}

Panel::Panel(Panel&& other) noexcept
{
    m_children = std::move(other.m_children);
    other.m_children.clear();
}

Panel& Panel::operator=(Panel&& other) noexcept
{
    if (this == &other)
        return *this;

    for (IElement* element : m_children)
        delete element;

    m_children = std::move(other.m_children);
    other.m_children.clear();
    return *this;
}

void Panel::update(double delta_time)
{
}

void Panel::render()
{
}

}