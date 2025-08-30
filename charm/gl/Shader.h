#pragma once

namespace charm::gl {

class Shader {
    unsigned int m_handle = 0;
    friend class Context;

    Shader(unsigned int handle);

public:
    Shader() = default;
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    unsigned int get() const;
};

}