#pragma once

#include "graphics/shaders/Program.h"

namespace charm {

class Material {
    Program m_program;

public:
    explicit Material() = default;
    explicit Material(Program&&);
    ~Material() = default;

    Material(const Material&) = delete;
    Material& operator=(const Material&) = delete;

    Material(Material&&);
    Material& operator=(Material&&);

    void use();
    void set_uniform(const std::string&, const Matrix4f&);
    void set_uniform(const std::string&, int);
};

}