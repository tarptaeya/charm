#pragma once

#include <string>
#include <unordered_map>

namespace charm {

class ShaderRegistry {
    friend class Application;

    std::unordered_map<std::string, unsigned int> m_shaders;
    explicit ShaderRegistry();

public:
    ~ShaderRegistry();

    ShaderRegistry(const ShaderRegistry&) = delete;
    ShaderRegistry& operator=(const ShaderRegistry&) = delete;

    void add_shader(unsigned int type, const std::string& path);
    unsigned int get_shader(const std::string& path) const;
};

}