#include "XMatrix4f.h"
#include <iostream>

XMatrix4f::XMatrix4f(const float (&data)[16])
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] = data[i];
    }
}

const float* XMatrix4f::get_data() const
{
    return m_data;
}

XMatrix4f& XMatrix4f::operator+=(const XMatrix4f& other)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] += other.m_data[i];
    }
    return *this;
}

XMatrix4f& XMatrix4f::operator-=(const XMatrix4f& other)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] -= other.m_data[i];
    }
    return *this;
}

XMatrix4f& XMatrix4f::operator*=(const XMatrix4f& other)
{
    float data[16] = { 0 };
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                data[i * 4 + j] += other.m_data[i * 4 + k] * m_data[k * 4 + j];
            }
        }
    }

    for (int i = 0; i < 16; ++i) {
        m_data[i] = data[i];
    }
    return *this;
}

XMatrix4f& XMatrix4f::operator*=(float x)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] *= x;
    }
    return *this;
}

XMatrix4f& XMatrix4f::operator/=(float x)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] /= x;
    }
    return *this;
}

XMatrix4f operator+(const XMatrix4f& a, const XMatrix4f& b)
{
    XMatrix4f ans;
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] = a.m_data[i] + b.m_data[i];
    }
    return ans;
}

XMatrix4f operator-(const XMatrix4f& a, const XMatrix4f& b)
{
    XMatrix4f ans;
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] = a.m_data[i] - b.m_data[i];
    }
    return ans;
}

XMatrix4f operator*(const XMatrix4f& a, const XMatrix4f& b)
{
    XMatrix4f ans;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                ans.m_data[i * 4 + j] += b.m_data[i * 4 + k] * a.m_data[k * 4 + j];
            }
        }
    }
    return ans;
}

XMatrix4f operator*(float x, const XMatrix4f& mat)
{
    XMatrix4f ans(mat);
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] *= x;
    }

    return ans;
}

XMatrix4f operator*(const XMatrix4f& mat, float x)
{
    XMatrix4f ans(mat);
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] *= x;
    }

    return ans;
}

XMatrix4f operator/(float x, const XMatrix4f& mat)
{
    XMatrix4f ans(mat);
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] /= x;
    }

    return ans;
}

XMatrix4f operator/(const XMatrix4f& mat, float x)
{
    XMatrix4f ans(mat);
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] /= x;
    }

    return ans;
}

XMatrix4f& XMatrix4f::inverse()
{
    float det = (m_data[0]) * (m_data[5] * m_data[10] * m_data[15] + m_data[9] * m_data[14] * m_data[7] + m_data[13] * m_data[6] * m_data[11] - m_data[13] * m_data[10] * m_data[7] - m_data[9] * m_data[6] * m_data[15] - m_data[5] * m_data[14] * m_data[11]) - (m_data[4]) * (m_data[1] * m_data[10] * m_data[15] + m_data[9] * m_data[14] * m_data[3] + m_data[13] * m_data[2] * m_data[11] - m_data[13] * m_data[10] * m_data[3] - m_data[9] * m_data[2] * m_data[15] - m_data[1] * m_data[14] * m_data[11]) + (m_data[8]) * (m_data[1] * m_data[6] * m_data[15] + m_data[5] * m_data[14] * m_data[3] + m_data[13] * m_data[2] * m_data[7] - m_data[13] * m_data[6] * m_data[3] - m_data[5] * m_data[2] * m_data[15] - m_data[1] * m_data[14] * m_data[7]) - (m_data[12]) * (m_data[1] * m_data[6] * m_data[11] + m_data[5] * m_data[10] * m_data[3] + m_data[9] * m_data[2] * m_data[7] - m_data[9] * m_data[6] * m_data[3] - m_data[5] * m_data[2] * m_data[11] - m_data[1] * m_data[10] * m_data[7]);
    float temp0 = 1 * (m_data[5] * m_data[10] * m_data[15] + m_data[9] * m_data[14] * m_data[7] + m_data[13] * m_data[6] * m_data[11] - m_data[13] * m_data[10] * m_data[7] - m_data[9] * m_data[6] * m_data[15] - m_data[5] * m_data[14] * m_data[11]);
    float temp4 = -1 * (m_data[4] * m_data[10] * m_data[15] + m_data[8] * m_data[14] * m_data[7] + m_data[12] * m_data[6] * m_data[11] - m_data[12] * m_data[10] * m_data[7] - m_data[8] * m_data[6] * m_data[15] - m_data[4] * m_data[14] * m_data[11]);
    float temp8 = 1 * (m_data[4] * m_data[9] * m_data[15] + m_data[8] * m_data[13] * m_data[7] + m_data[12] * m_data[5] * m_data[11] - m_data[12] * m_data[9] * m_data[7] - m_data[8] * m_data[5] * m_data[15] - m_data[4] * m_data[13] * m_data[11]);
    float temp12 = -1 * (m_data[4] * m_data[9] * m_data[14] + m_data[8] * m_data[13] * m_data[6] + m_data[12] * m_data[5] * m_data[10] - m_data[12] * m_data[9] * m_data[6] - m_data[8] * m_data[5] * m_data[14] - m_data[4] * m_data[13] * m_data[10]);
    float temp1 = -1 * (m_data[1] * m_data[10] * m_data[15] + m_data[9] * m_data[14] * m_data[3] + m_data[13] * m_data[2] * m_data[11] - m_data[13] * m_data[10] * m_data[3] - m_data[9] * m_data[2] * m_data[15] - m_data[1] * m_data[14] * m_data[11]);
    float temp5 = 1 * (m_data[0] * m_data[10] * m_data[15] + m_data[8] * m_data[14] * m_data[3] + m_data[12] * m_data[2] * m_data[11] - m_data[12] * m_data[10] * m_data[3] - m_data[8] * m_data[2] * m_data[15] - m_data[0] * m_data[14] * m_data[11]);
    float temp9 = -1 * (m_data[0] * m_data[9] * m_data[15] + m_data[8] * m_data[13] * m_data[3] + m_data[12] * m_data[1] * m_data[11] - m_data[12] * m_data[9] * m_data[3] - m_data[8] * m_data[1] * m_data[15] - m_data[0] * m_data[13] * m_data[11]);
    float temp13 = 1 * (m_data[0] * m_data[9] * m_data[14] + m_data[8] * m_data[13] * m_data[2] + m_data[12] * m_data[1] * m_data[10] - m_data[12] * m_data[9] * m_data[2] - m_data[8] * m_data[1] * m_data[14] - m_data[0] * m_data[13] * m_data[10]);
    float temp2 = 1 * (m_data[1] * m_data[6] * m_data[15] + m_data[5] * m_data[14] * m_data[3] + m_data[13] * m_data[2] * m_data[7] - m_data[13] * m_data[6] * m_data[3] - m_data[5] * m_data[2] * m_data[15] - m_data[1] * m_data[14] * m_data[7]);
    float temp6 = -1 * (m_data[0] * m_data[6] * m_data[15] + m_data[4] * m_data[14] * m_data[3] + m_data[12] * m_data[2] * m_data[7] - m_data[12] * m_data[6] * m_data[3] - m_data[4] * m_data[2] * m_data[15] - m_data[0] * m_data[14] * m_data[7]);
    float temp10 = 1 * (m_data[0] * m_data[5] * m_data[15] + m_data[4] * m_data[13] * m_data[3] + m_data[12] * m_data[1] * m_data[7] - m_data[12] * m_data[5] * m_data[3] - m_data[4] * m_data[1] * m_data[15] - m_data[0] * m_data[13] * m_data[7]);
    float temp14 = -1 * (m_data[0] * m_data[5] * m_data[14] + m_data[4] * m_data[13] * m_data[2] + m_data[12] * m_data[1] * m_data[6] - m_data[12] * m_data[5] * m_data[2] - m_data[4] * m_data[1] * m_data[14] - m_data[0] * m_data[13] * m_data[6]);
    float temp3 = -1 * (m_data[1] * m_data[6] * m_data[11] + m_data[5] * m_data[10] * m_data[3] + m_data[9] * m_data[2] * m_data[7] - m_data[9] * m_data[6] * m_data[3] - m_data[5] * m_data[2] * m_data[11] - m_data[1] * m_data[10] * m_data[7]);
    float temp7 = 1 * (m_data[0] * m_data[6] * m_data[11] + m_data[4] * m_data[10] * m_data[3] + m_data[8] * m_data[2] * m_data[7] - m_data[8] * m_data[6] * m_data[3] - m_data[4] * m_data[2] * m_data[11] - m_data[0] * m_data[10] * m_data[7]);
    float temp11 = -1 * (m_data[0] * m_data[5] * m_data[11] + m_data[4] * m_data[9] * m_data[3] + m_data[8] * m_data[1] * m_data[7] - m_data[8] * m_data[5] * m_data[3] - m_data[4] * m_data[1] * m_data[11] - m_data[0] * m_data[9] * m_data[7]);
    float temp15 = 1 * (m_data[0] * m_data[5] * m_data[10] + m_data[4] * m_data[9] * m_data[2] + m_data[8] * m_data[1] * m_data[6] - m_data[8] * m_data[5] * m_data[2] - m_data[4] * m_data[1] * m_data[10] - m_data[0] * m_data[9] * m_data[6]);
    m_data[0] = temp0 / det;
    m_data[4] = temp4 / det;
    m_data[8] = temp8 / det;
    m_data[12] = temp12 / det;
    m_data[1] = temp1 / det;
    m_data[5] = temp5 / det;
    m_data[9] = temp9 / det;
    m_data[13] = temp13 / det;
    m_data[2] = temp2 / det;
    m_data[6] = temp6 / det;
    m_data[10] = temp10 / det;
    m_data[14] = temp14 / det;
    m_data[3] = temp3 / det;
    m_data[7] = temp7 / det;
    m_data[11] = temp11 / det;
    m_data[15] = temp15 / det;
    return *this;
}

XMatrix4f XMatrix4f::identity()
{
    XMatrix4f ans;
    ans.m_data[0] = ans.m_data[5] = ans.m_data[10] = ans.m_data[15] = 1;
    return ans;
}

XMatrix4f XMatrix4f::scaling(float value)
{
    // clang-format off
    return XMatrix4f({
        value, 0, 0, 0,
        0, value, 0, 0,
        0, 0, value, 0,
        0, 0, 0, 1,
    });
    // clang-format on
}

XMatrix4f XMatrix4f::scaling(float x, float y, float z)
{
    // clang-format off
    return XMatrix4f({
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1,
    });
    // clang-format on
}

XMatrix4f XMatrix4f::rotation_x(float theta)
{
    // clang-format off
    return XMatrix4f({
        1, 0,      0,       0,
        0, cos(theta), -sin(theta), 0,
        0, sin(theta), cos(theta),  0,
        0, 0,      0,       1,
    });
    // clang-format on
}

XMatrix4f XMatrix4f::rotation_y(float theta)
{
    // clang-format off
    return XMatrix4f({
        cos(theta), 0, -sin(theta), 0,
        0,          1, 0,           0,
        sin(theta), 0, cos(theta),  0,
        0,          0, 0,           1,
    });
    // clang-format on
}

XMatrix4f XMatrix4f::rotation_z(float theta)
{
    // clang-format off
    return XMatrix4f({
        cos(theta),  sin(theta), 0, 0,
        -sin(theta), cos(theta), 0, 0,
        0,           0,          1, 0,
        0,           0,          0, 1,
    });
    // clang-format on
}

XMatrix4f XMatrix4f::translation(float x, float y, float z)
{
    // clang-format off
    return XMatrix4f({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1,
    });
    // clang-format on
}

XMatrix4f XMatrix4f::perspective(float fov, float aspect_ratio, float near, float far)
{
    // clang-format off
    return XMatrix4f({
        1 / (aspect_ratio * tan(fov / 2)), 0,                0,                              0,
        0,                                 1 / tan(fov / 2), 0,                              0,
        0,                                 0,                -(far + near) / (far - near),   -1,
        0,                                 0,                -2 * far * near / (far - near), 0,
    });
    // clang-format on
}

XMatrix4f XMatrix4f::look_at(const XVector4f& position, const XVector4f& target, const XVector4f& world_up)
{
    XVector4f direction = (position - target).normalized();
    XVector4f right = XVector4f::cross(world_up, direction).normalized();
    XVector4f up = XVector4f::cross(direction, right).normalized();

    // clang-format off
    XMatrix4f change_of_basis({
        right.x(), up.x(), direction.x(), 0,
        right.y(), up.y(), direction.y(), 0,
        right.z(), up.z(), direction.z(), 0,
        0,         0,      0,             1,
    });
    // clang-format on

    return change_of_basis * translation(-position.x(), -position.y(), -position.z());
}