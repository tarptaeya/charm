#pragma once

namespace charm::gl {

class Program {
    unsigned int m_handle = 0;
    friend class Context;

    Program(unsigned int handle);

public:
    Program() = default;
    ~Program();

    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;

    unsigned int get() const;
};

}