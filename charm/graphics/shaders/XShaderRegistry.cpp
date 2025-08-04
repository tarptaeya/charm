#include "XShaderRegistry.h"
#include "io/XFileIO.h"
#include <glad/gl.h>
#include <iostream>

XShaderRegistry::XShaderRegistry()
{
}

XShaderRegistry::~XShaderRegistry()
{
    for (const auto& entry : m_shaders) {
        glDeleteShader(entry.second);
    }
}

void XShaderRegistry::add_shader(unsigned int type, const std::string& path)
{
    if (m_shaders.count(path)) {
        return;
    }

    unsigned int shader = glCreateShader(type);
    std::string source = XFileIO::read_text(path);
    const char* raw_source = source.c_str();
    glShaderSource(shader, 1, &raw_source, nullptr);
    glCompileShader(shader);
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char log[512];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        glDeleteShader(shader);
        std::cerr << "[error] " << log << std::endl;
        std::exit(1);
    }

    m_shaders[path] = shader;
}

unsigned int XShaderRegistry::get_shader(const std::string& path) const
{
    return m_shaders.at(path);
}
