#pragma once

namespace charm::gl {

class Buffer {
    unsigned int m_handle = 0;
    friend class Context;

    Buffer(unsigned int handle);

public:
    Buffer() = default;
    ~Buffer();

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    Buffer(Buffer&&);
    Buffer& operator=(Buffer&&);

    unsigned int get() const;
};

}