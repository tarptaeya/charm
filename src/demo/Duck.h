#pragma once

#include "charm.h"
#include <vector>

class Duck {
    std::vector<charm::Geometry> m_geometries;

    Duck();

public:
    ~Duck();
    Duck(const Duck&) = delete;
    Duck& operator=(const Duck&) = delete;

    Duck(Duck&&);
    Duck& operator=(Duck&&);

    std::vector<charm::Geometry>::const_iterator begin() const;
    std::vector<charm::Geometry>::const_iterator end() const;

    static Duck& get_instance();
};