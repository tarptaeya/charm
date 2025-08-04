#include "Vector4f.h"

namespace charm {

Vector4f::Vector4f(float x, float y, float z)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
}

Vector4f::Vector4f(float x, float y, float z, float w)
{
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
    m_data[3] = z;
}

float Vector4f::operator[](int index)
{
    return m_data[index];
}

float Vector4f::x() const
{
    return m_data[0];
}

float Vector4f::y() const
{
    return m_data[1];
}

float Vector4f::z() const
{
    return m_data[2];
}

const float* Vector4f::get_data() const
{
    return m_data;
}

}
