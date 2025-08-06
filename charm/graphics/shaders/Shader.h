#pragma once

#include <glad/gl.h>
#include <string>

namespace charm {

class Shader {
    GLuint m_shader = 0;
    friend class Program;

public:
    Shader() = default;
    Shader(GLuint type, const std::string& source);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&&);
    Shader& operator=(Shader&&);
};

}