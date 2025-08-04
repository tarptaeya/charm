#pragma once

class XVector4f {
    float m_data[4] = { 0 };

public:
    explicit XVector4f(float, float, float);
    explicit XVector4f(float, float, float, float);

    float operator[](int);

    float x() const;
    float y() const;
    float z() const;

    const float* get_data() const;
};
