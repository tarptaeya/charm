#pragma once

#include "math/XMatrix4f.h"
#include <iostream>
#include <string>
#include <unordered_map>

class XProgram {
    unsigned int m_program = 0;
    std::unordered_map<std::string, int> m_uniform_locations;

public:
    XProgram() = default;
    explicit XProgram(unsigned int vertex_shader, unsigned int fragment_shader);
    ~XProgram();

    XProgram(const XProgram&) = delete;
    XProgram& operator=(const XProgram&) = delete;

    XProgram(XProgram&&);
    XProgram& operator=(XProgram&&);

    void use();
    void set_uniform(const std::string&, const XMatrix4f&);
    void set_uniform(const std::string&, int);
};
