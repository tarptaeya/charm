#pragma once

namespace charm::gl {

class Texture {
    unsigned int m_handle = 0;

public:
    Texture() = default;
    Texture(unsigned int handle);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&&);
    Texture& operator=(Texture&&);

    [[nodiscard]] unsigned int get() const;
};

}