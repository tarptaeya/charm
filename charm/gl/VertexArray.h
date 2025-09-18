#pragma once

namespace charm::gl {

class VertexArray {
    unsigned int m_handle = 0;

public:
    VertexArray() = default;
    VertexArray(unsigned int handle);
    ~VertexArray();

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    VertexArray(VertexArray&&);
    VertexArray& operator=(VertexArray&&);

    [[nodiscard]] unsigned int get() const;
};

}
