#pragma once

#include <fstream>

namespace charm {

class BinaryIO {
public:
    static int read_int(std::ifstream&);
    static unsigned int read_unsigned_int(std::ifstream&);
    static float read_float(std::ifstream&);

    static void write(std::ofstream&, int);
    static void write(std::ofstream&, unsigned int);
    static void write(std::ofstream&, float);
};

}