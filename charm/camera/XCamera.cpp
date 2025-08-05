#include "XCamera.h"
#include <iostream>

const XMatrix4f& XCamera::get_view() const
{
    return m_view;
}

XMatrix4f XCamera::get_projection() const
{
    return m_projection;
}

void XCamera::set_view(const XMatrix4f& view)
{
    m_view = view;
}

void XCamera::set_view(XMatrix4f&& view)
{
    m_view = std::move(view);
}

void XCamera::set_projection(const XMatrix4f& projection)
{
    m_projection = projection;
}

void XCamera::set_projection(XMatrix4f&& projection)
{
    m_projection = std::move(projection);
}
