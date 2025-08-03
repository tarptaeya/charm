#pragma once

#include "Geometry.h"

namespace charm {

class BoxGeometry : public Geometry {
public:
    explicit BoxGeometry();
    ~BoxGeometry() = default;

    BoxGeometry(const BoxGeometry&) = delete;
    BoxGeometry& operator=(const BoxGeometry&) = delete;

    BoxGeometry(BoxGeometry&&) = default;
    BoxGeometry& operator=(BoxGeometry&&) = default;
};

}