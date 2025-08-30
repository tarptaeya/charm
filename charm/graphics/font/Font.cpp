#include "Font.h"
#include "charm.h"

namespace charm {

Font::Font(const std::string& texture_path, const std::string& metadata_path)
{
    m_metadata = FontMetadata::parse(metadata_path);
    m_texture = Texture2DBuilder(texture_path)
                    .set_texture_unit(GL_TEXTURE1)
                    .build();
}

gl::Texture& Font::get_texture()
{
    return m_texture;
}

FontMetadata& Font::get_metadata()
{
    return m_metadata;
}

}