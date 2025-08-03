#pragma once

#include "graphics/shaders/ShaderProgram.h"

namespace charm {

class Material {
    ShaderProgram m_shader_program;

public:
    explicit Material() = default;
    explicit Material(ShaderProgram&&);
    ~Material() = default;

    Material(const Material&) = delete;
    Material& operator=(const Material&) = delete;

    Material(Material&&);
    Material& operator=(Material&&);

    ShaderProgram& get_shader_program();
};

}