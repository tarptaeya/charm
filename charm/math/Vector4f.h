#pragma once

namespace charm {

class Vector4f {
    float m_data[4] = { 0 };
    Vector4f() = default;

public:
    explicit Vector4f(float, float, float);
    explicit Vector4f(float, float, float, float);

    ~Vector4f() = default;

    Vector4f(const Vector4f&) = default;
    Vector4f& operator=(const Vector4f&) = default;

    Vector4f(Vector4f&&) = default;
    Vector4f& operator=(Vector4f&&) = default;

    float& operator[](int);

    float x() const;
    float y() const;
    float z() const;

    Vector4f normalized() const;
    const float* get_data() const;

    friend Vector4f operator+(const Vector4f&, const Vector4f&);
    friend Vector4f operator-(const Vector4f&, const Vector4f&);

    static Vector4f cross(const Vector4f&, const Vector4f&);
};

}