#pragma once

#include "graphics/shaders/XProgram.h"

class XMaterial {
    XProgram m_program;

public:
    explicit XMaterial() = default;
    explicit XMaterial(XProgram&&);
    ~XMaterial() = default;

    XMaterial(const XMaterial&) = delete;
    XMaterial& operator=(const XMaterial&) = delete;

    XMaterial(XMaterial&&);
    XMaterial& operator=(XMaterial&&);

    XProgram& get_program();
};
