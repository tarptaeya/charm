#pragma once

#include "math/Mat4.h"
#include <fstream>

namespace charm {

class BinaryIO {
public:
    static int read_int(std::ifstream&);
    static unsigned int read_unsigned_int(std::ifstream&);
    static float read_float(std::ifstream&);
    static std::string read_string(std::ifstream&);
    static Mat4 read_mat4(std::ifstream&);

    static void write(std::ofstream&, int);
    static void write(std::ofstream&, unsigned int);
    static void write(std::ofstream&, float);
    static void write(std::ofstream&, const std::string&);
    static void write(std::ofstream&, const Mat4&);
};

}