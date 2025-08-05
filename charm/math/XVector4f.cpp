#include "XVector4f.h"
#include <cmath>

XVector4f::XVector4f(float x, float y, float z)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
}

XVector4f::XVector4f(float x, float y, float z, float w)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
    m_data[3] = w;
}

float& XVector4f::operator[](int index)
{
    return m_data[index];
}

float XVector4f::x() const
{
    return m_data[0];
}

float XVector4f::y() const
{
    return m_data[1];
}

float XVector4f::z() const
{
    return m_data[2];
}

XVector4f XVector4f::normalized() const
{
    float length = 0;
    for (int i = 0; i < 4; ++i) {
        length += m_data[i] * m_data[i];
    }
    length = sqrt(length);

    return XVector4f(m_data[0] / length, m_data[1] / length, m_data[2] / length, m_data[3] / length);
}

const float* XVector4f::get_data() const
{
    return m_data;
}

XVector4f operator+(const XVector4f& a, const XVector4f& b)
{
    XVector4f ans;
    for (int i = 0; i < 4; ++i) {
        ans.m_data[i] = a.m_data[i] + b.m_data[i];
    }
    return ans;
}

XVector4f operator-(const XVector4f& a, const XVector4f& b)
{
    XVector4f ans;
    for (int i = 0; i < 4; ++i) {
        ans.m_data[i] = a.m_data[i] - b.m_data[i];
    }
    return ans;
}

XVector4f XVector4f::cross(const XVector4f& a, const XVector4f& b)
{
    float x = a.y() * b.z() - a.z() * b.y();
    float y = a.z() * b.x() - a.x() * b.z();
    float z = a.x() * b.y() - a.y() * b.x();
    return XVector4f(x, y, z);
}