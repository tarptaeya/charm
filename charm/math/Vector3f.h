#pragma once

namespace charm {

class Vector3f {
    float m_data[3] = { 0 };
    Vector3f() = default;

public:
    explicit Vector3f(float, float, float);

    ~Vector3f() = default;

    Vector3f(const Vector3f&) = default;
    Vector3f& operator=(const Vector3f&) = default;

    Vector3f(Vector3f&&) = default;
    Vector3f& operator=(Vector3f&&) = default;

    float& operator[](int);

    float x() const;
    float y() const;
    float z() const;

    Vector3f normalized() const;
    const float* get_data() const;

    friend Vector3f operator+(const Vector3f&, const Vector3f&);
    friend Vector3f operator-(const Vector3f&, const Vector3f&);

    static Vector3f cross(const Vector3f&, const Vector3f&);
};

}