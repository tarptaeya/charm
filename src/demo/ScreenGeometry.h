#pragma once

#include "charm.h"

class ScreenGeometry {
    ScreenGeometry();
    charm::Geometry m_geometry;

public:
    ~ScreenGeometry();

    ScreenGeometry(const ScreenGeometry&) = delete;
    ScreenGeometry& operator=(const ScreenGeometry&) = delete;

    ScreenGeometry(ScreenGeometry&&);
    ScreenGeometry& operator=(ScreenGeometry&&);

    const charm::Geometry& get_geometry() const;

    static ScreenGeometry& get_instance();
};