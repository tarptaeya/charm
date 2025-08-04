#pragma once

class XAppAdapter {
public:
    virtual ~XAppAdapter() = default;
    virtual void update(double delta_time) = 0;
};
