#pragma once

namespace charm::gl {

class Buffer {
    unsigned int m_handle = 0;

public:
    Buffer() = default;
    Buffer(unsigned int handle);
    ~Buffer();

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    Buffer(Buffer&&);
    Buffer& operator=(Buffer&&);

    [[nodiscard]] unsigned int get() const;
};

}