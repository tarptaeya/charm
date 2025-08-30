#pragma once

#include "Program.h"
#include "Shader.h"
#include <string>

namespace charm::gl {

class Context {
public:
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    Shader create_shader(int type, const std::string& source);
    Program create_program(const std::string& vertex_source, const std::string& fragment_source);

    static const int VERTEX_SHADER;
    static const int FRAGMENT_SHADER;
};

}