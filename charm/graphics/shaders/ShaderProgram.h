#pragma once

#include "math/Matrix4f.h"
#include <iostream>
#include <string>
#include <unordered_map>

namespace charm {

class ShaderProgram {
    unsigned int m_program = 0;
    std::unordered_map<std::string, int> m_uniform_locations;

public:
    ShaderProgram() = default;
    explicit ShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader);
    ~ShaderProgram();

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&&);
    ShaderProgram& operator=(ShaderProgram&&);

    void use();
    void set_uniform(const std::string&, const Matrix4f&);
    void set_uniform(const std::string&, int);
};

}