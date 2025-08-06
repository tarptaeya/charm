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

void Material::use()
{
    glUseProgram(m_program.m_id);
}

void Material::set_uniform(const std::string& name, const Matrix4f& value)
{
    m_program.set_uniform(name, value);
}

void Material::set_uniform(const std::string& name, int value)
{
    m_program.set_uniform(name, value);
}

}