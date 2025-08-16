#pragma once

#include "FontMetadata.h"
#include <string>

namespace charm {

namespace imui {

    void begin(int x, int y, int width, int height, const FontMetadata&);
    void end();

    void label(const std::string&);

}

}