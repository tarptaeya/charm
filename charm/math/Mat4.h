#pragma once

#include "Vec3.h"

namespace charm {

class Mat4 {
    float m_data[16] = { 0 };

public:
    Mat4() = default;
    Mat4(const float (&)[4][4]);
    ~Mat4() = default;

    Mat4(const Mat4&) = default;
    Mat4& operator=(const Mat4&) = default;

    const float* get_data() const;
    Mat4& inverse();
    Mat4 inversed() const;

    float operator()(int x, int y) const;
    float& operator()(int x, int y);
    Mat4& operator+=(const Mat4&);
    Mat4& operator-=(const Mat4&);
    Mat4& operator*=(const Mat4&);
    Mat4& operator*=(float);
    Mat4& operator/=(float);

    friend Mat4 operator+(const Mat4&, const Mat4&);
    friend Mat4 operator-(const Mat4&, const Mat4&);
    friend Mat4 operator*(const Mat4&, const Mat4&);
    friend Mat4 operator*(float, const Mat4&);
    friend Mat4 operator*(const Mat4&, float);
    friend Mat4 operator/(const Mat4&, float);

    static Mat4 identity();

    static Mat4 scaling(float);
    static Mat4 scaling(float, float, float);

    static Mat4 rotation_x(float);
    static Mat4 rotation_y(float);
    static Mat4 rotation_z(float);

    static Mat4 translation(float, float, float);

    static Mat4 perspective(float vertical_fov, float aspect_ratio, float near, float far);
    static Mat4 look_at(const Vec3& position, const Vec3& target, const Vec3& world_up);

    static Mat4 ortho(float width, float height, float near, float far);
};

}