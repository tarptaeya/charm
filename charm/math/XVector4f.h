#pragma once

class XVector4f {
    float m_data[4] = { 0 };
    XVector4f() = default;

public:
    explicit XVector4f(float, float, float);
    explicit XVector4f(float, float, float, float);

    ~XVector4f() = default;

    XVector4f(const XVector4f&) = default;
    XVector4f& operator=(const XVector4f&) = default;

    XVector4f(XVector4f&&) = default;
    XVector4f& operator=(XVector4f&&) = default;

    float operator[](int);

    float x() const;
    float y() const;
    float z() const;

    XVector4f normalized() const;
    const float* get_data() const;

    friend XVector4f operator+(const XVector4f&, const XVector4f&);
    friend XVector4f operator-(const XVector4f&, const XVector4f&);

    static XVector4f cross(const XVector4f&, const XVector4f&);
};
