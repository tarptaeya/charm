#pragma once

namespace charm {

class AppAdapter {
public:
    virtual ~AppAdapter() = default;
    virtual void update(double delta_time) = 0;
};

}