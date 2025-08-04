#pragma once

#include "graphics/textures/XImageData.h"
#include <string>

class XPPMReader {
public:
    static XImageData read(const std::string&);
};
