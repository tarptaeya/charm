#pragma once

#include "math/Matrix4f.h"

namespace charm {

class Camera {
public:
    Matrix4f m_view;
    Matrix4f m_projection;

public:
    explicit Camera() = default;
    ~Camera() = default;

    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

    const Matrix4f& get_view() const;
    Matrix4f get_projection() const;

    void set_view(const Matrix4f&);
    void set_view(Matrix4f&&);
    void set_projection(const Matrix4f&);
    void set_projection(Matrix4f&&);
};

}