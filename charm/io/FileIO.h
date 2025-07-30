#pragma once

#include <string>

namespace charm {

class FileIO {
public:
    static std::string read_text(const std::string&);
};

}