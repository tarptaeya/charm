#include "Material.h"

#include <iostream>

namespace charm {

Material::Material(Program&& program)
    : m_program(std::move(program))
{
}

Material::Material(Material&& other)
{
    m_program = std::move(other.m_program);
}

Material& Material::operator=(Material&& other)
{
    if (this == &other)
        return *this;

    m_program = std::move(other.m_program);
    return *this;
}

Program& Material::get_program()
{
    return m_program;
}

}