#pragma once

namespace charm {

class Matrix4f {
    float m_data[16] = { 0 };

public:
    Matrix4f() = default;
    ~Matrix4f() = default;

    Matrix4f(const Matrix4f&) = default;
    Matrix4f& operator=(const Matrix4f&) = default;

    Matrix4f(Matrix4f&&) = default;
    Matrix4f& operator=(Matrix4f&&) = default;

    const float* get_data() const;

    static Matrix4f identity();
};

}