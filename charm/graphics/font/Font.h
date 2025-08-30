#pragma once

#include "FontMetadata.h"
#include "gl/Texture.h"

namespace charm {

class Font {
    gl::Texture m_texture;
    FontMetadata m_metadata;

public:
    Font(const std::string& texture_path, const std::string& metadata_path);
    Font(const Font&) = delete;
    Font& operator=(const Font&) = delete;

    gl::Texture& get_texture();
    FontMetadata& get_metadata();
};

}