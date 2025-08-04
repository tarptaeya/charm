#pragma once

#include "math/XMatrix4f.h"

class XCamera {
public:
    XMatrix4f m_transform;
    XMatrix4f m_projection;

public:
    explicit XCamera() = default;
    ~XCamera() = default;

    XCamera(const XCamera&) = delete;
    XCamera& operator=(const XCamera&) = delete;

    const XMatrix4f& get_transform() const;
    void set_transform(const XMatrix4f&);

    XMatrix4f get_view() const;
    XMatrix4f get_projection() const;

    void set_projection(const XMatrix4f&);
    void set_projection(XMatrix4f&&);
};
