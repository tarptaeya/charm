#pragma once

#include "charm.h"

class DemoAdapter : public charm::AppAdapter {
public:
    DemoAdapter();
    ~DemoAdapter() override;

    void update(double delta_time) override;
};