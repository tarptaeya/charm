#pragma once

#include "ui/FontMetadata.h"
#include <string>

namespace charm {

class FontIO {
public:
    static FontMetadata parse_metadata(const std::string& path);
};

}