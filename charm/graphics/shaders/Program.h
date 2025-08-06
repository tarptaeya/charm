#pragma once

#include "Shader.h"
#include "math/Matrix4f.h"
#include <iostream>
#include <string>
#include <unordered_map>

namespace charm {

class Program {
    friend class Material;

    unsigned int m_id = 0;
    std::unordered_map<std::string, int> m_uniform_locations;

public:
    Program() = default;
    explicit Program(const Shader&, const Shader&);
    ~Program();

    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;

    Program(Program&&);
    Program& operator=(Program&&);

    void use();
    void set_uniform(const std::string&, const Matrix4f&);
    void set_uniform(const std::string&, int);
};

}