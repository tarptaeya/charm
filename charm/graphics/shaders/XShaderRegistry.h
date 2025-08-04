#pragma once

#include <string>
#include <unordered_map>

class XShaderRegistry {
    friend class XApplication;

    std::unordered_map<std::string, unsigned int> m_shaders;
    explicit XShaderRegistry();

public:
    ~XShaderRegistry();

    XShaderRegistry(const XShaderRegistry&) = delete;
    XShaderRegistry& operator=(const XShaderRegistry&) = delete;

    void add_shader(unsigned int type, const std::string& path);
    unsigned int get_shader(const std::string& path) const;
};
