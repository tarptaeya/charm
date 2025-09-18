#pragma once

#include <string>
#include <unordered_map>

namespace charm::gl {

class Program {
    unsigned int m_handle = 0;

public:
    std::unordered_map<std::string, int> uniform_locations;

    Program() = default;
    Program(unsigned int handle);
    ~Program();

    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;

    Program(Program&&);
    Program& operator=(Program&&);

    [[nodiscard]] unsigned int get() const;
};

}