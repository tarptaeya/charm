#include "XImageData.h"

XImageData::XImageData(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_data(width * height * 3)
{
}

int XImageData::get_width() const
{
    return m_width;
}

int XImageData::get_height() const
{
    return m_height;
}

std::vector<unsigned char>& XImageData::get_data()
{
    return m_data;
}
