#include "FileIO.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace charm {

std::string FileIO::read_text(const std::string& path)
{
    std::ifstream f(path);
    if (!f) {
        std::cerr << "[error] unable to read path: " << path << std::endl;
        std::exit(1);
    }
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

}