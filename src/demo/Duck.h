#pragma once

#include "charm.h"
#include <unordered_map>
#include <vector>

class Duck {
    charm::ch3db::Model m_model;
    std::vector<charm::Geometry> m_geometries;
    std::unordered_map<int, charm::Mat4> m_joint_transforms;

public:
    Duck();
    ~Duck();
    Duck(const Duck&) = delete;
    Duck& operator=(const Duck&) = delete;

    Duck(Duck&&);
    Duck& operator=(Duck&&);

    std::vector<charm::Geometry>::const_iterator begin() const;
    std::vector<charm::Geometry>::const_iterator end() const;

    void update(double delta_time);
    void setup_joint_uniform(charm::gl::Program&);

private:
    void apply_animation(charm::ch3db::Skeleton* node, charm::Mat4 parent_transform, float tick);
};