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

Matrix4f Matrix4f::identity()
{
    Matrix4f ans;
    ans.m_data[0] = ans.m_data[5] = ans.m_data[10] = ans.m_data[15] = 1;
    return ans;
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

}
