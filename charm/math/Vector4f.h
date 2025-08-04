#pragma once

namespace charm {

class Vector4f {
    float m_data[4] = { 0 };

public:
    explicit Vector4f(float, float, float);
    explicit Vector4f(float, float, float, float);

    float operator[](int);

    float x() const;
    float y() const;
    float z() const;

    const float* get_data() const;
};

}