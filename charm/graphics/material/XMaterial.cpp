#include "XMaterial.h"

#include <iostream>

XMaterial::XMaterial(XProgram&& program)
    : m_program(std::move(program))
{
}

XMaterial::XMaterial(XMaterial&& other)
{
    m_program = std::move(other.m_program);
}

XMaterial& XMaterial::operator=(XMaterial&& other)
{
    if (this == &other)
        return *this;

    m_program = std::move(other.m_program);
    return *this;
}

XProgram& XMaterial::get_program()
{
    return m_program;
}
