#pragma once

namespace charm {

class Vec3 {
    float m_data[3] = { 0 };
    Vec3() = default;

public:
    explicit Vec3(float, float, float);

    ~Vec3() = default;

    Vec3(const Vec3&) = default;
    Vec3& operator=(const Vec3&) = default;

    Vec3(Vec3&&) = default;
    Vec3& operator=(Vec3&&) = default;

    float& operator[](int);

    float x() const;
    float y() const;
    float z() const;

    Vec3 normalized() const;
    const float* get_data() const;

    friend Vec3 operator+(const Vec3&, const Vec3&);
    friend Vec3 operator-(const Vec3&, const Vec3&);

    static Vec3 cross(const Vec3&, const Vec3&);
};

}