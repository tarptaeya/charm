#include "ImageData.h"

namespace charm {

ImageData::ImageData(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_data(width * height * 3)
{
}

int ImageData::get_width() const
{
    return m_width;
}

int ImageData::get_height() const
{
    return m_height;
}

std::vector<unsigned char>& ImageData::get_data()
{
    return m_data;
}

}