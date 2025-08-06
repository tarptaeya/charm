#pragma once

#include "graphics/textures/ImageData.h"
#include <string>

namespace charm {

class PPMReader {
public:
    static ImageData read(const std::string&);
};

}