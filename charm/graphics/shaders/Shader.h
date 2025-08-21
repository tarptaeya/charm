#pragma once

#include "math/Matrix4f.h"
#include <glad/gl.h>
#include <string>
#include <unordered_map>

namespace charm {

class Shader {
    GLuint m_program = 0;
    std::unordered_map<std::string, int> m_uniform_locations;

public:
    Shader() = default;
    Shader(GLuint program);
    Shader(const std::string& vertex_source, const std::string& fragment_source);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&&);
    Shader& operator=(Shader&&);

    [[nodiscard]] GLuint get_gl_program() const;

    void use();
    void set_uniform(const std::string&, const Matrix4f&);
    void set_uniform(const std::string&, int);
};

}