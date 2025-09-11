#pragma once

#include <string>
#include <vector>

namespace charm {

struct Color {
    float r, g, b;

    bool operator==(const Color&) const;
};

struct Texcoord {
    float u, v;
};

namespace utils {

    std::vector<std::string> split(const std::string&, char);

}

}