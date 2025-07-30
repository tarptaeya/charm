#pragma once

#include <iostream>
#include <string>

namespace charm {

class ShaderProgram {
    unsigned int m_program = 0;

public:
    ShaderProgram() = default;
    explicit ShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader);
    ~ShaderProgram();

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&&);
    ShaderProgram& operator=(ShaderProgram&&);

    void use();
};

}