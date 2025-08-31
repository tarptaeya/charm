#pragma once

namespace charm::gl {

class Framebuffer {
    unsigned int m_handle = 0;

    friend class Context;
    Framebuffer(unsigned int handle);

public:
    Framebuffer() = default;
    ~Framebuffer();

    Framebuffer(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    Framebuffer(Framebuffer&&);
    Framebuffer& operator=(Framebuffer&&);

    unsigned int get() const;
};

}