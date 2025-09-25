#pragma once

#include "graphics/skybox/Skybox.h"

namespace charm {

class Environment {
    std::unique_ptr<Skybox> m_skybox = nullptr;

public:
    Environment() = default;

    Skybox* get_skybox();
    void set_skybox(std::unique_ptr<Skybox>& skybox);
};

}
