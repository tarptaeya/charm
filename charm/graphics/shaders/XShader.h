#pragma once

#include <glad/gl.h>
#include <string>

class XShader {
    GLuint m_shader = 0;
    friend class XProgram;

public:
    XShader() = default;
    XShader(GLuint, const std::string&);
    ~XShader();

    XShader(const XShader&) = delete;
    XShader& operator=(const XShader&) = delete;

    XShader(XShader&&);
    XShader& operator=(XShader&&);
};