#pragma once

namespace charm {

class Matrix4f {
    float m_data[16] = { 0 };

public:
    Matrix4f() = default;
    Matrix4f(const float (&)[16]);
    ~Matrix4f() = default;

    Matrix4f(const Matrix4f&) = default;
    Matrix4f& operator=(const Matrix4f&) = default;

    Matrix4f(Matrix4f&&) = default;
    Matrix4f& operator=(Matrix4f&&) = default;

    const float* get_data() const;

    Matrix4f& operator+=(const Matrix4f&);
    Matrix4f& operator-=(const Matrix4f&);
    Matrix4f& operator*=(const Matrix4f&);
    Matrix4f& operator*=(float);
    Matrix4f& operator/=(float);

    friend Matrix4f operator+(const Matrix4f&, const Matrix4f&);
    friend Matrix4f operator-(const Matrix4f&, const Matrix4f&);
    friend Matrix4f operator*(const Matrix4f&, const Matrix4f&);
    friend Matrix4f operator*(float, const Matrix4f&);
    friend Matrix4f operator*(const Matrix4f&, float);
    friend Matrix4f operator/(float, const Matrix4f&);
    friend Matrix4f operator/(const Matrix4f&, float);

    static Matrix4f identity();
};

}