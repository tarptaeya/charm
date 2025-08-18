#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <fstream>
#include <iostream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct CharacterInfo {
    char c;
    int x, y; // Position in texture atlas
    int width, height; // width, height of bbox in texture atlas
    int xoffset;
    int yoffset;
    int xadvance;
    unsigned char* bitmap_buffer;
};

int main(int argc, const char** argv)
{
    FT_Library library;
    if (FT_Init_FreeType(&library)) {
        std::cerr << "[error] cannot initialize freetype" << std::endl;
        std::exit(1);
    }

    FT_Face face;
    if (FT_New_Face(library, argv[1], 0, &face)) {
        std::cerr << "[error] cannot load font" << std::endl;
        std::exit(1);
    }

    int font_pixel_height = 64;
    FT_Set_Pixel_Sizes(face, 0, font_pixel_height);

    std::vector<CharacterInfo> all_info;
    for (char c = 32; c < 127; ++c) {
        FT_Load_Char(face, c, FT_LOAD_RENDER);
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_SDF);

        if (face->glyph->bitmap.width != face->glyph->bitmap.pitch) {
            std::cerr << "[error] bitmap width != bitmap pitch for [" << c << "]" << std::endl;
            std::exit(1);
        }

        CharacterInfo info;
        info.c = c;
        info.width = face->glyph->bitmap.width;
        info.height = face->glyph->bitmap.rows;
        info.xoffset = face->glyph->bitmap_left;
        info.yoffset = face->glyph->bitmap_top;
        info.xadvance = face->glyph->advance.x / 64; // Freetype metrics are expressed in 26.6 pixel format (i.e. 1/64th of pixel)
        info.bitmap_buffer = static_cast<unsigned char*>(malloc(info.width * info.height));
        std::memcpy(info.bitmap_buffer, face->glyph->bitmap.buffer, info.width * info.height);
        all_info.push_back(info);
    }

    int xcurr = 0;
    int line_height = 0;
    int num_rows = 1;
    int max_allowed_width = 1024;
    for (int i = 0; i < all_info.size(); ++i) {
        if (xcurr + all_info[i].width <= max_allowed_width) {
            xcurr += all_info[i].width;
        } else {
            num_rows += 1;
            xcurr = all_info[i].width;
        }
        line_height = std::max(all_info[i].height, line_height);
    }

    int total_width = max_allowed_width;
    int total_height = num_rows * line_height;

    unsigned char* atlas_buffer = static_cast<unsigned char*>(malloc(total_width * total_height));
    std::memset(atlas_buffer, 0, total_width * total_height);
    int xcursor = 0;
    int ycursor = 0;
    for (auto& info : all_info) {
        if (xcursor + info.width > total_width) {
            xcursor = 0;
            ycursor += line_height;
        }

        info.x = xcursor;
        info.y = ycursor;
        for (int y = 0; y < info.height; ++y) {
            for (int x = 0; x < info.width; ++x) {
                atlas_buffer[(y + ycursor) * total_width + (x + xcursor)] = info.bitmap_buffer[y * info.width + x];
            }
        }
        xcursor += info.width;
    }

    stbi_write_png("bitmap.png", total_width, total_height, 1, atlas_buffer, total_width);
    std::ofstream f("font.txt");
    f << total_width << " " << total_height << " " << font_pixel_height << std::endl;
    for (const auto& info : all_info) {
        f << info.c << " "
          << info.x << " "
          << info.y << " "
          << info.width << " "
          << info.height << " "
          << info.xoffset << " "
          << info.yoffset << " "
          << info.xadvance << std::endl;
    }
}