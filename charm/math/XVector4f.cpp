#include "XVector4f.h"

XVector4f::XVector4f(float x, float y, float z)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
}

XVector4f::XVector4f(float x, float y, float z, float w)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
    m_data[3] = z;
}

float XVector4f::operator[](int index)
{
    return m_data[index];
}

float XVector4f::x() const
{
    return m_data[0];
}

float XVector4f::y() const
{
    return m_data[1];
}

float XVector4f::z() const
{
    return m_data[2];
}

const float* XVector4f::get_data() const
{
    return m_data;
}
