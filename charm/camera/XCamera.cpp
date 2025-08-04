#include "XCamera.h"
#include <iostream>

const XMatrix4f& XCamera::get_transform() const
{
    return m_transform;
}

void XCamera::set_transform(const XMatrix4f& transform)
{
    m_transform = transform;
}

XMatrix4f XCamera::get_view() const
{
    XMatrix4f view(m_transform);
    view.inverse();
    return view;
}

XMatrix4f XCamera::get_projection() const
{
    return m_projection;
}

void XCamera::set_projection(const XMatrix4f& projection)
{
    m_projection = projection;
}

void XCamera::set_projection(XMatrix4f&& projection)
{
    m_projection = std::move(projection);
}
