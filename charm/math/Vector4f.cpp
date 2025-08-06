#include "Vector4f.h"
#include <cmath>

namespace charm {

Vector4f::Vector4f(float x, float y, float z)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
}

Vector4f::Vector4f(float x, float y, float z, float w)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
    m_data[3] = w;
}

float& Vector4f::operator[](int index)
{
    return m_data[index];
}

float Vector4f::x() const
{
    return m_data[0];
}

float Vector4f::y() const
{
    return m_data[1];
}

float Vector4f::z() const
{
    return m_data[2];
}

Vector4f Vector4f::normalized() const
{
    float length = 0;
    for (int i = 0; i < 4; ++i) {
        length += m_data[i] * m_data[i];
    }
    length = sqrt(length);

    return Vector4f(m_data[0] / length, m_data[1] / length, m_data[2] / length, m_data[3] / length);
}

const float* Vector4f::get_data() const
{
    return m_data;
}

Vector4f operator+(const Vector4f& a, const Vector4f& b)
{
    Vector4f ans;
    for (int i = 0; i < 4; ++i) {
        ans.m_data[i] = a.m_data[i] + b.m_data[i];
    }
    return ans;
}

Vector4f operator-(const Vector4f& a, const Vector4f& b)
{
    Vector4f ans;
    for (int i = 0; i < 4; ++i) {
        ans.m_data[i] = a.m_data[i] - b.m_data[i];
    }
    return ans;
}

Vector4f Vector4f::cross(const Vector4f& a, const Vector4f& b)
{
    float x = a.y() * b.z() - a.z() * b.y();
    float y = a.z() * b.x() - a.x() * b.z();
    float z = a.x() * b.y() - a.y() * b.x();
    return Vector4f(x, y, z);
}

}