#include "XPPMReader.h"
#include <fstream>
#include <iostream>

static void skip_whitespace_and_comments(std::ifstream& f)
{
    while (true) {
        if (std::isspace(f.peek())) {
            f.get();
        } else if (f.peek() == '#') {
            std::string line;
            std::getline(f, line);
        } else {
            break;
        }
    }
}

XImageData XPPMReader::read(const std::string& path)
{
    std::ifstream f(path);
    if (!f) {
        std::cerr << "[error] unable to read ppm image: " << path << std::endl;
        std::exit(1);
    }

    skip_whitespace_and_comments(f);
    std::string magic_number;
    f >> magic_number;
    if (magic_number != "P6") {
        std::cerr << "[error] magic number is not supported for ppm image: " << magic_number << std::endl;
        std::exit(1);
    }

    skip_whitespace_and_comments(f);
    int width, height, max_color_value;
    f >> width >> height >> max_color_value;

    if (max_color_value != 255) {
        std::cerr << "[error] max color value is not supported for ppm image: " << max_color_value << std::endl;
        std::exit(1);
    }

    skip_whitespace_and_comments(f);
    XImageData image_data(width, height);
    f.read(reinterpret_cast<char*>(&image_data.get_data()[0]), image_data.get_data().size() * sizeof(unsigned char));
    return image_data;
}
