#pragma once

#include <string>
#include <unordered_map>

namespace charm::gl {

class Program {
    unsigned int m_handle = 0;
    std::unordered_map<std::string, int> m_uniform_locations;

    friend class Context;
    Program(unsigned int handle);

public:
    Program() = default;
    ~Program();

    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;

    Program(Program&&);
    Program& operator=(Program&&);

    [[nodiscard]] unsigned int get() const;
};

}