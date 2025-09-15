#include "Mat4.h"
#include <cmath>

namespace charm {

Mat4::Mat4(const float (&data)[4][4])
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->operator()(i, j) = data[i][j];
        }
    }
}

const float* Mat4::get_data() const
{
    return m_data;
}

Mat4& Mat4::inverse()
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

Mat4 Mat4::inversed() const
{
    Mat4 ans(*this);
    ans.inverse();
    return ans;
}

float Mat4::operator()(int x, int y) const
{
    return m_data[x + y * 4];
}

float& Mat4::operator()(int x, int y)
{
    return m_data[x + y * 4];
}

Mat4& Mat4::operator+=(const Mat4& other)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] += other.m_data[i];
    }
    return *this;
}

Mat4& Mat4::operator-=(const Mat4& other)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] -= other.m_data[i];
    }
    return *this;
}

Mat4& Mat4::operator*=(const Mat4& other)
{
    float data[4][4] = { 0 };
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                data[i][j] += this->operator()(i, k) * other(k, j);
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->operator()(i, j) = data[i][j];
        }
    }
    return *this;
}

Mat4& Mat4::operator*=(float k)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] *= k;
    }
    return *this;
}

Mat4& Mat4::operator/=(float k)
{
    for (int i = 0; i < 16; ++i) {
        m_data[i] /= k;
    }
    return *this;
}

Mat4 Mat4::identity()
{
    // clang-format off
    return Mat4({ 
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 } 
    });
    // clang-format on
}

Mat4 Mat4::scaling(float k)
{
    // clang-format off
    return Mat4({ 
        { k, 0, 0, 0 },
        { 0, k, 0, 0 },
        { 0, 0, k, 0 },
        { 0, 0, 0, 1 } 
    });
    // clang-format on
}

Mat4 Mat4::scaling(float x, float y, float z)
{
    // clang-format off
    return Mat4({ 
        { x, 0, 0, 0 },
        { 0, y, 0, 0 },
        { 0, 0, z, 0 },
        { 0, 0, 0, 1 } 
    });
    // clang-format on
}

Mat4 Mat4::rotation_x(float theta)
{
    // clang-format off
    return Mat4({ 
        { 1, 0,          0,           0 },
        { 0, cos(theta), -sin(theta), 0 },
        { 0, sin(theta), cos(theta),  0 },
        { 0, 0,          0,           1 } 
    });
    // clang-format on
}

Mat4 Mat4::rotation_y(float theta)
{
    // clang-format off
    return Mat4({ 
        { cos(theta),  0, sin(theta), 0 },
        { 0,           1, 0,          0 },
        { -sin(theta), 0, cos(theta), 0 },
        { 0,           0, 0,          1 } 
    });
    // clang-format on
}

Mat4 Mat4::rotation_z(float theta)
{
    // clang-format off
    return Mat4({ 
        { cos(theta), -sin(theta), 0, 0 },
        { sin(theta), cos(theta),  0, 0 },
        { 0,          0,           1, 0 },
        { 0,          0,           0, 1 } 
    });
    // clang-format on
}

Mat4 Mat4::translation(float x, float y, float z)
{
    // clang-format off
    return Mat4({ 
        { 1, 0, 0, x },
        { 0, 1, 0, y },
        { 0, 0, 1, z },
        { 0, 0, 0, 1 } 
    });
    // clang-format on
}

Mat4 Mat4::perspective(float vertical_fov, float aspect_ratio, float near, float far)
{
    float tangent = tan(vertical_fov / 2);

    // clang-format off
    return Mat4({ 
        { 1 / (aspect_ratio * tangent), 0,           0,                            0                              },
        { 0,                            1 / tangent, 0,                            0                              },
        { 0,                            0,           -(far + near) / (far - near), -2 * far * near / (far - near) },
        { 0,                            0,           -1,                           0                              } 
    });
    // clang-format on
}

Mat4 Mat4::look_at(const Vector3f& position, const Vector3f& target, const Vector3f& world_up)
{
    Vector3f direction = (position - target).normalized();
    Vector3f right = Vector3f::cross(world_up, direction).normalized();
    Vector3f up = Vector3f::cross(direction, right).normalized();

    // clang-format off
    Mat4 change_of_basis({
        { right.x(),     right.y(),     right.z(),     0 },
        { up.x(),        up.y(),        up.z(),        0 },
        { direction.x(), direction.y(), direction.z(), 0 },
        { 0,             0,             0,             1 }
    });
    // clang-format on

    return change_of_basis * translation(-position.x(), -position.y(), -position.z());
}

Mat4 operator+(const Mat4& a, const Mat4& b)
{
    Mat4 ans(a);
    ans += b;
    return ans;
}

Mat4 operator-(const Mat4& a, const Mat4& b)
{
    Mat4 ans(a);
    ans -= b;
    return ans;
}

Mat4 operator*(const Mat4& a, const Mat4& b)
{
    Mat4 ans(a);
    ans *= b;
    return ans;
}

Mat4 operator*(float k, const Mat4& a)
{
    Mat4 ans(a);
    ans *= k;
    return ans;
}

Mat4 operator*(const Mat4& a, float k)
{
    Mat4 ans(a);
    ans *= k;
    return ans;
}

Mat4 operator/(const Mat4& a, float k)
{
    Mat4 ans(a);
    ans /= k;
    return ans;
}

}