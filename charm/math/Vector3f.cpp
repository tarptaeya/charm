#include "Vector3f.h"
#include <cmath>

namespace charm {

Vector3f::Vector3f(float x, float y, float z)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
}

float& Vector3f::operator[](int index)
{
    return m_data[index];
}

float Vector3f::x() const
{
    return m_data[0];
}

float Vector3f::y() const
{
    return m_data[1];
}

float Vector3f::z() const
{
    return m_data[2];
}

Vector3f Vector3f::normalized() const
{
    float length = 0;
    for (int i = 0; i < 3; ++i) {
        length += m_data[i] * m_data[i];
    }
    length = sqrt(length);

    return Vector3f(m_data[0] / length, m_data[1] / length, m_data[2] / length);
}

const float* Vector3f::get_data() const
{
    return m_data;
}

Vector3f operator+(const Vector3f& a, const Vector3f& b)
{
    Vector3f ans;
    for (int i = 0; i < 3; ++i) {
        ans.m_data[i] = a.m_data[i] + b.m_data[i];
    }
    return ans;
}

Vector3f operator-(const Vector3f& a, const Vector3f& b)
{
    Vector3f ans;
    for (int i = 0; i < 3; ++i) {
        ans.m_data[i] = a.m_data[i] - b.m_data[i];
    }
    return ans;
}

Vector3f Vector3f::cross(const Vector3f& a, const Vector3f& b)
{
    float x = a.y() * b.z() - a.z() * b.y();
    float y = a.z() * b.x() - a.x() * b.z();
    float z = a.x() * b.y() - a.y() * b.x();
    return Vector3f(x, y, z);
}

}