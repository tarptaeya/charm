#pragma once

#include "XGeometry.h"

class XBoxGeometry : public XGeometry {
public:
    explicit XBoxGeometry();
    ~XBoxGeometry() = default;

    XBoxGeometry(const XBoxGeometry&) = delete;
    XBoxGeometry& operator=(const XBoxGeometry&) = delete;

    XBoxGeometry(XBoxGeometry&&) = default;
    XBoxGeometry& operator=(XBoxGeometry&&) = default;
};
