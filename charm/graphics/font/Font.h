#pragma once

#include "graphics/textures/Texture2D.h"
#include "ui/FontMetadata.h"

namespace charm {

class Font {
    Texture2D m_texture;
    FontMetadata m_metadata;

public:
    Font(const std::string& texture_path, const std::string& metadata_path);
    Font(const Font&) = delete;
    Font& operator=(const Font&) = delete;

    Texture2D& get_texture();
    FontMetadata& get_metadata();
};

}