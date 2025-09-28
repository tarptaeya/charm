#pragma once

#include "DirectionalLight.h"
#include "gl/Context.h"
#include "graphics/skybox/Skybox.h"

namespace charm {

class Environment {
    std::unique_ptr<Skybox> m_skybox = nullptr;
    DirectionalLight m_directional_light;

public:
    Environment() = default;

    Skybox* get_skybox();
    void set_skybox(std::unique_ptr<Skybox>& skybox);

    DirectionalLight& get_directional_light();
    void set_directional_light(const DirectionalLight&);

    void set_uniforms(gl::Program&) const;
};

}
