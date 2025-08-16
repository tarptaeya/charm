#define STB_TRUETYPE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "stb_truetype.h"
#include <fstream>
#include <iostream>

#define width 512
#define height 512
#define pixel_height 64

unsigned char buffer[1 << 25];
unsigned char bitmap[width * height];
stbtt_bakedchar cdata[95];

int main(int argc, const char** argv)
{
    if (argc != 2) {
        std::cout << "[usage] font-conv path-to-font.ttf" << std::endl;
        std::exit(0);
    }
    fread(buffer, 1, 1 << 25, fopen(argv[1], "rb"));

    int start_char = 32;
    int num_char = 95;
    stbtt_BakeFontBitmap(buffer, 0, pixel_height, bitmap, width, height, start_char, num_char, cdata);
    stbi_write_png("bitmap.png", width, height, 1, bitmap, width);

    std::ofstream f("font.txt");
    f << width << " " << height << std::endl;
    for (int i = 0; i < num_char; ++i) {
        char c = start_char + i;
        f << c << " "
          << cdata[i].x0 << " "
          << cdata[i].y0 << " "
          << cdata[i].x1 << " "
          << cdata[i].y1 << " "
          << cdata[i].xoff << " "
          << cdata[i].yoff << " "
          << cdata[i].xadvance << std::endl;
    }
}