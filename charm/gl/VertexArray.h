#pragma once

namespace charm::gl {

class VertexArray {
    unsigned int m_handle = 0;
    friend class Context;

    VertexArray(unsigned int handle);

public:
    VertexArray() = default;
    ~VertexArray();

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    VertexArray(VertexArray&&);
    VertexArray& operator=(VertexArray&&);

    [[nodiscard]] unsigned int get() const;
};

}
