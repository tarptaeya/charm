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

}