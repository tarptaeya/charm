#pragma once

namespace charm {

class AppAdapter {
public:
    virtual ~AppAdapter() = 0;
    virtual void update(double delta_time) = 0;
};

}