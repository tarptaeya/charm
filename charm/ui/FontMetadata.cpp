#include "FontMetadata.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace charm {

FontMetadata FontMetadata::parse(const std::string& path)
{
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cerr << "[error] unable to parse font metadata: " << path << std::endl;
        std::exit(0);
    }

    FontMetadata metadata;
    f >> metadata.bitmap_width >> metadata.bitmap_height >> metadata.bitmap_pixel_height;

    std::string line;
    while (std::getline(f, line)) {
        std::stringstream ss(line);
        char c = ss.get();
        int x, y, width, height;
        int xoffset, yoffset, xadvance;
        ss >> x >> y >> width >> height >> xoffset >> yoffset >> xadvance;
        metadata.info[c].x = x;
        metadata.info[c].y = y;
        metadata.info[c].width = width;
        metadata.info[c].height = height;
        metadata.info[c].xoffset = xoffset;
        metadata.info[c].yoffset = yoffset;
        metadata.info[c].xadvance = xadvance;
    }

    return metadata;
}

}