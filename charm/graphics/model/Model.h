#pragma once

#include "ch3db/ch3db.h"
#include "gl/Buffer.h"
#include "gl/Program.h"
#include "gl/VertexArray.h"
#include <vector>

namespace charm {

class Model {
    std::shared_ptr<ch3db::Skeleton> m_root_node = nullptr;
    std::vector<ch3db::Animation> m_animations;
    std::vector<gl::VertexArray> m_vertex_arrays;
    std::vector<gl::Buffer> m_buffers;
    std::vector<unsigned int> m_triangle_counts;

    double m_timer = 0;
    int m_current_animation_index = -1;
    std::unordered_map<int, charm::Mat4> m_joint_transforms;

public:
    Model() = default;
    Model(const std::string& path);
    ~Model();

    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    Model(Model&&);
    Model& operator=(Model&&);

    std::vector<std::string> get_animations() const;
    void set_current_animation(const std::string&);
    void reset_animation_timer();

    void update(double delta_time);

    void set_joint_uniforms(gl::Program&);
    void draw();

private:
    void traverse_nodes(charm::ch3db::Skeleton* node, const charm::Mat4& parent_transform, float tick);
};

}