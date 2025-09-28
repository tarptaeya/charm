#include "Environment.h"

namespace charm {

Skybox* Environment::get_skybox()
{
    return m_skybox.get();
}

void Environment::set_skybox(std::unique_ptr<Skybox>& skybox)
{
    m_skybox = std::move(skybox);
}

DirectionalLight& Environment::get_directional_light()
{
    return m_directional_light;
}

void Environment::set_directional_light(const DirectionalLight& directional_light)
{
    m_directional_light = directional_light;
}

void Environment::set_uniforms(gl::Program& program) const
{
    gl::set_uniform(program, "u_directional_light.direction", m_directional_light.direction);
    gl::set_uniform(program, "u_directional_light.ambient", m_directional_light.ambient);
    gl::set_uniform(program, "u_directional_light.diffuse", m_directional_light.diffuse);
    gl::set_uniform(program, "u_directional_light.specular", m_directional_light.specular);
}

}