#pragma once

#include <iostream>

#define ASSERT_TRUE(x) \
    if (!(x))          \
        std::exit(1);