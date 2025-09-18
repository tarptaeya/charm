#pragma once

#include "Mat4.h"

namespace charm {

class Quat {
    float m_w = 0;
    float m_x = 0;
    float m_y = 0;
    float m_z = 0;

public:
    Quat(float w, float x, float y, float z);

    void normalize();
    Quat normalized() const;
    Mat4 to_rotation() const;
    static Quat slerp(const Quat& a, const Quat& b, float t);

    friend Quat operator+(const Quat&, const Quat&);
    friend Quat operator*(float, const Quat&);
};

}