#include "Camera.h"
#include <iostream>

namespace charm {

const Mat4& Camera::get_view() const
{
    return m_view;
}

Mat4 Camera::get_projection() const
{
    return m_projection;
}

void Camera::set_view(const Mat4& view)
{
    m_view = view;
}

void Camera::set_view(Mat4&& view)
{
    m_view = std::move(view);
}

void Camera::set_projection(const Mat4& projection)
{
    m_projection = projection;
}

void Camera::set_projection(Mat4&& projection)
{
    m_projection = std::move(projection);
}

}