#pragma once

namespace charm::gl {

class Texture {
    unsigned int m_handle = 0;
    friend class Context;

    Texture(unsigned int handle);

public:
    Texture() = default;
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&&);
    Texture& operator=(Texture&&);

    [[nodiscard]] unsigned int get() const;
};

}