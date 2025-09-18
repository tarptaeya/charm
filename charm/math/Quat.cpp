#include "Quat.h"
#include <cmath>

namespace charm {

Quat::Quat(float w, float x, float y, float z)
    : m_w(w)
    , m_x(x)
    , m_y(y)
    , m_z(z)
{
}

void Quat::normalize()
{
    float len = sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
    if (len == 0) {
        m_w = 1;
        m_x = m_y = m_z = 0;
        return;
    }
    m_w /= len;
    m_x /= len;
    m_y /= len;
    m_z /= len;
}

Quat Quat::normalized() const
{
    Quat ans(m_w, m_x, m_y, m_z);
    ans.normalize();
    return ans;
}

Mat4 Quat::to_rotation() const
{
    auto q = normalized();
    return charm::Mat4({
        // clang-format off
        { 1 - 2 * (q.m_y * q.m_y + q.m_z * q.m_z),     2 * (q.m_x * q.m_y - q.m_w * q.m_z),     2 * (q.m_x * q.m_z + q.m_w * q.m_y),     0 },
        { 2 * (q.m_x * q.m_y + q.m_w * q.m_z),         1 - 2 * (q.m_x * q.m_x + q.m_z * q.m_z), 2 * (q.m_y * q.m_z - q.m_w * q.m_x),     0 },
        { 2 * (q.m_x * q.m_z - q.m_w * q.m_y),         2 * (q.m_y * q.m_z + q.m_w * q.m_x),     1 - 2 * (q.m_x * q.m_x + q.m_y * q.m_y), 0 },
        { 0,                                   0,                               0,                               1 }
        // clang-format on
    });
}

Quat Quat::slerp(const Quat& first, const Quat& second, float t)
{
    Quat a = first.normalized();
    Quat b = second.normalized();

    float dot = a.m_w * b.m_w + a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z;
    dot = fmax(-1, fmin(dot, 1));
    if (dot > 0.999) {
        // if cos(theta) is close to 1, then sin(theta) will be close to 0
        // which could result in division by 0. To mitigate this, use lerp
        // for small angles
        Quat ans = (1 - t) * a + t * b;
        ans.normalize();
        return ans;
    }
    if (dot < 0) {
        dot *= -1;
        b = -1 * b;
    }
    float theta = acos(dot);
    Quat ans = sin((1 - t) * theta) / sin(theta) * a + sin(t * theta) / sin(theta) * b;
    ans.normalize();
    return ans;
}

Quat operator+(const Quat& a, const Quat& b)
{
    return Quat(a.m_w + b.m_w, a.m_x + b.m_x, a.m_y + b.m_y, a.m_z + b.m_z);
}

Quat operator*(float k, const Quat& a)
{
    return Quat(k * a.m_w, k * a.m_x, k * a.m_y, k * a.m_z);
}

}