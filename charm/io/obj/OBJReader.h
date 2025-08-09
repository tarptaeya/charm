#pragma once

#include "graphics/geometry/Geometry.h"
#include <string>

namespace charm {

class OBJReader {
public:
    static Geometry read_geometry(const std::string&);
};

}