#pragma once

namespace charm::gl {

class Framebuffer {
    unsigned int m_handle = 0;

public:
    Framebuffer() = default;
    Framebuffer(unsigned int handle);
    ~Framebuffer();

    Framebuffer(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    Framebuffer(Framebuffer&&);
    Framebuffer& operator=(Framebuffer&&);

    unsigned int get() const;
};

}