#pragma once

namespace charm::gl {

class Shader {
    unsigned int m_handle = 0;

public:
    Shader(unsigned int handle);

    Shader() = default;
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    [[nodiscard]] unsigned int get() const;
};

}