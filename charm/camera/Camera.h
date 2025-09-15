#pragma once

#include "math/Mat4.h"

namespace charm {

class Camera {
public:
    Mat4 m_view;
    Mat4 m_projection;

public:
    explicit Camera() = default;
    ~Camera() = default;

    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

    const Mat4& get_view() const;
    Mat4 get_projection() const;

    void set_view(const Mat4&);
    void set_view(Mat4&&);
    void set_projection(const Mat4&);
    void set_projection(Mat4&&);
};

}