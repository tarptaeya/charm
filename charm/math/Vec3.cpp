#include "Vec3.h"
#include <cmath>

namespace charm {

Vec3::Vec3(float x, float y, float z)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
}

float& Vec3::operator[](int index)
{
    return m_data[index];
}

float Vec3::x() const
{
    return m_data[0];
}

float Vec3::y() const
{
    return m_data[1];
}

float Vec3::z() const
{
    return m_data[2];
}

Vec3 Vec3::normalized() const
{
    float length = 0;
    for (int i = 0; i < 3; ++i) {
        length += m_data[i] * m_data[i];
    }
    length = sqrt(length);

    return Vec3(m_data[0] / length, m_data[1] / length, m_data[2] / length);
}

const float* Vec3::get_data() const
{
    return m_data;
}

Vec3 operator+(const Vec3& a, const Vec3& b)
{
    Vec3 ans;
    for (int i = 0; i < 3; ++i) {
        ans.m_data[i] = a.m_data[i] + b.m_data[i];
    }
    return ans;
}

Vec3 operator-(const Vec3& a, const Vec3& b)
{
    Vec3 ans;
    for (int i = 0; i < 3; ++i) {
        ans.m_data[i] = a.m_data[i] - b.m_data[i];
    }
    return ans;
}

Vec3 operator*(float k, const Vec3& a)
{
    return Vec3(k * a.x(), k * a.y(), k * a.z());
}

Vec3 Vec3::cross(const Vec3& a, const Vec3& b)
{
    float x = a.y() * b.z() - a.z() * b.y();
    float y = a.z() * b.x() - a.x() * b.z();
    float z = a.x() * b.y() - a.y() * b.x();
    return Vec3(x, y, z);
}

Vec3 Vec3::lerp(const Vec3& a, const Vec3& b, float t)
{
    return (1 - t) * a + t * b;
}

}