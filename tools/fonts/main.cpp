#define STB_TRUETYPE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include "stb_truetype.h"
#include <iostream>

#define width 512
#define height 512

unsigned char buffer[1 << 20];
unsigned char bitmap[width * height];
stbtt_bakedchar cdata[96];

int main(int argc, const char** argv)
{
    if (argc != 3) {
        std::cout << "[usage] font-conv path-to-font.ttf output-name" << std::endl;
        std::exit(0);
    }
    fread(buffer, 1, 1 << 20, fopen(argv[1], "rb"));
    stbtt_BakeFontBitmap(buffer, 0, 32, bitmap, width, height, 32, 96, cdata);
    stbi_write_png(argv[2], width, height, 1, bitmap, width);
}