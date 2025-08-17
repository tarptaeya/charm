#include "FontIO.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace charm {

FontMetadata FontIO::parse_metadata(const std::string& path)
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
        int x0, y0, x1, y1;
        int xoffset, yoffset, xadvance;
        ss >> x0 >> y0 >> x1 >> y1 >> xoffset >> yoffset >> xadvance;
        metadata.info[c].x0 = x0;
        metadata.info[c].y0 = y0;
        metadata.info[c].x1 = x1;
        metadata.info[c].y1 = y1;
        metadata.info[c].xoffset = xoffset;
        metadata.info[c].yoffset = yoffset;
        metadata.info[c].xadvance = xadvance;
    }

    return metadata;
}

}