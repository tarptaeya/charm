#include "Material.h"

#include <iostream>

namespace charm {

Material::Material(ShaderProgram&& shader_program)
    : m_shader_program(std::move(shader_program))
{
}

Material::Material(Material&& other)
{
    m_shader_program = std::move(other.m_shader_program);
}

Material& Material::operator=(Material&& other)
{
    if (this == &other)
        return *this;

    m_shader_program = std::move(other.m_shader_program);
    return *this;
}

ShaderProgram& Material::get_shader_program()
{
    return m_shader_program;
}

}