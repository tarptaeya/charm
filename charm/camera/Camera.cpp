#include "Camera.h"
#include <iostream>

namespace charm {

const Matrix4f& Camera::get_transform() const
{
    return m_transform;
}

void Camera::set_transform(const Matrix4f& transform)
{
    m_transform = transform;
}

Matrix4f Camera::get_view() const
{
    Matrix4f view(m_transform);
    view.inverse();
    return view;
}

Matrix4f Camera::get_projection() const
{
    return m_projection;
}

void Camera::set_projection(const Matrix4f& projection)
{
    m_projection = projection;
}

void Camera::set_projection(Matrix4f&& projection)
{
    m_projection = std::move(projection);
}

}