#include "Matrix4f.h"
#include <iostream>

namespace charm {

Matrix4f::Matrix4f(const float (&data)[16])
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] = data[i];
    }
}

const float* Matrix4f::get_data() const
{
    return m_data;
}

Matrix4f& Matrix4f::operator+=(const Matrix4f& other)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] += other.m_data[i];
    }
    return *this;
}

Matrix4f& Matrix4f::operator-=(const Matrix4f& other)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] -= other.m_data[i];
    }
    return *this;
}

Matrix4f& Matrix4f::operator*=(const Matrix4f& other)
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

Matrix4f& Matrix4f::operator*=(float x)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] *= x;
    }
    return *this;
}

Matrix4f& Matrix4f::operator/=(float x)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] /= x;
    }
    return *this;
}

Matrix4f operator+(const Matrix4f& a, const Matrix4f& b)
{
    Matrix4f ans;
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] = a.m_data[i] + b.m_data[i];
    }
    return ans;
}

Matrix4f operator-(const Matrix4f& a, const Matrix4f& b)
{
    Matrix4f ans;
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] = a.m_data[i] - b.m_data[i];
    }
    return ans;
}

Matrix4f operator*(const Matrix4f& a, const Matrix4f& b)
{
    Matrix4f ans;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                ans.m_data[i * 4 + j] += b.m_data[i * 4 + k] * a.m_data[k * 4 + j];
            }
        }
    }
    return ans;
}

Matrix4f operator*(float x, const Matrix4f& mat)
{
    Matrix4f ans(mat);
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] *= x;
    }

    return ans;
}

Matrix4f operator*(const Matrix4f& mat, float x)
{
    Matrix4f ans(mat);
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] *= x;
    }

    return ans;
}

Matrix4f operator/(float x, const Matrix4f& mat)
{
    Matrix4f ans(mat);
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] /= x;
    }

    return ans;
}

Matrix4f operator/(const Matrix4f& mat, float x)
{
    Matrix4f ans(mat);
    for (int i = 0; i < 16; ++i) {
        ans.m_data[i] /= x;
    }

    return ans;
}

Matrix4f& Matrix4f::inverse()
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

Matrix4f Matrix4f::identity()
{
    Matrix4f ans;
    ans.m_data[0] = ans.m_data[5] = ans.m_data[10] = ans.m_data[15] = 1;
    return ans;
}

Matrix4f Matrix4f::scaling(float value)
{
    // clang-format off
    return Matrix4f({
        value, 0, 0, 0,
        0, value, 0, 0,
        0, 0, value, 0,
        0, 0, 0, 1,
    });
    // clang-format on
}

Matrix4f Matrix4f::scaling(float x, float y, float z)
{
    // clang-format off
    return Matrix4f({
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1,
    });
    // clang-format on
}

Matrix4f Matrix4f::translation(float x, float y, float z)
{
    // clang-format off
    return Matrix4f({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1,
    });
    // clang-format on
}

Matrix4f Matrix4f::perspective(float fov, float aspect_ratio, float near, float far)
{
    // clang-format off
    return Matrix4f({
        1 / (aspect_ratio * tan(fov / 2)), 0,                0,                              0,
        0,                                 1 / tan(fov / 2), 0,                              0,
        0,                                 0,                -(far + near) / (far - near),   -1,
        0,                                 0,                -2 * far * near / (far - near), 0,
    });
    // clang-format on
}

}
