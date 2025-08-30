#pragma once

namespace charm::gl {

class Program {
    unsigned int m_handle = 0;
    friend class Context;

    Program() = default;
    Program(unsigned int handle);

public:
    ~Program();
    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;

    unsigned int get() const;
};

}