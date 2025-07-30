#include "Matrix4f.h"

namespace charm {

const float* Matrix4f::get_data() const
{
    return m_data;
}

Matrix4f Matrix4f::identity()
{
    Matrix4f ans;
    ans.m_data[0] = ans.m_data[5] = ans.m_data[10] = ans.m_data[15] = 1;
    return ans;
}

}