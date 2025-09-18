#include "Model.h"
#include "gl/Context.h"
#include "math/Mat4.h"
#include "math/Quat.h"
#include "math/Vec3.h"

namespace charm {

Model::Model(const std::string& path)
{
    ch3db::Model raw_model = ch3db::Model::read(path);
    m_root_node = raw_model.root;
    m_animations = raw_model.animations;

    for (const auto& mesh : raw_model.meshes) {
        auto vertex_array = gl::gen_vertex_array();
        gl::bind(vertex_array);

        auto vertex_buffer = gl::gen_buffer();
        gl::bind(GL_ARRAY_BUFFER, vertex_buffer);
        gl::buffer_data(GL_ARRAY_BUFFER, sizeof(ch3db::Vertex) * mesh.vertices.size(), &mesh.vertices[0], GL_STATIC_DRAW);

        gl::enable_vertex_attrib_array(0);
        gl::vertex_attrib_pointer(0, 3, GL_FLOAT, false, sizeof(ch3db::Vertex), (void*)(offsetof(ch3db::Vertex, position)));
        gl::enable_vertex_attrib_array(1);
        gl::vertex_attrib_pointer(1, 3, GL_FLOAT, false, sizeof(ch3db::Vertex), (void*)(offsetof(ch3db::Vertex, normal)));
        gl::enable_vertex_attrib_array(2);
        gl::vertex_attrib_pointer(2, 2, GL_FLOAT, false, sizeof(ch3db::Vertex), (void*)(offsetof(ch3db::Vertex, texcoord)));
        gl::enable_vertex_attrib_array(3);
        gl::vertex_attribi_pointer(3, 4, GL_INT, sizeof(ch3db::Vertex), (void*)(offsetof(ch3db::Vertex, bone_ids)));
        gl::enable_vertex_attrib_array(4);
        gl::vertex_attrib_pointer(4, 4, GL_FLOAT, false, sizeof(ch3db::Vertex), (void*)(offsetof(ch3db::Vertex, bone_weights)));

        auto index_buffer = gl::gen_buffer();
        gl::bind(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        gl::buffer_data(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indices.size(), &mesh.indices[0], GL_STATIC_DRAW);

        m_vertex_arrays.push_back(std::move(vertex_array));
        m_buffers.push_back(std::move(vertex_buffer));
        m_buffers.push_back(std::move(index_buffer));
        m_triangle_counts.push_back(mesh.indices.size());
    }
}

Model::~Model()
{
}

Model::Model(Model&& other)
{
    m_root_node = std::move(other.m_root_node);
    m_animations = std::move(other.m_animations);
    m_vertex_arrays = std::move(other.m_vertex_arrays);
    m_buffers = std::move(other.m_buffers);
    m_triangle_counts = std::move(other.m_triangle_counts);
    m_timer = other.m_timer;
    m_current_animation_index = other.m_current_animation_index;
    m_joint_transforms = std::move(other.m_joint_transforms);

    other.m_root_node = nullptr;
    other.m_animations.clear();
    other.m_vertex_arrays.clear();
    other.m_buffers.clear();
    other.m_triangle_counts.clear();
    other.m_joint_transforms.clear();
}

Model& Model::operator=(Model&& other)
{
    if (this == &other)
        return *this;

    m_root_node = std::move(other.m_root_node);
    m_animations = std::move(other.m_animations);
    m_vertex_arrays = std::move(other.m_vertex_arrays);
    m_buffers = std::move(other.m_buffers);
    m_triangle_counts = std::move(other.m_triangle_counts);
    m_timer = other.m_timer;
    m_current_animation_index = other.m_current_animation_index;
    m_joint_transforms = std::move(other.m_joint_transforms);

    other.m_root_node = nullptr;
    other.m_animations.clear();
    other.m_vertex_arrays.clear();
    other.m_buffers.clear();
    other.m_triangle_counts.clear();
    other.m_joint_transforms.clear();

    return *this;
}

std::vector<std::string> Model::get_animations() const
{
    std::vector<std::string> ans;
    for (const auto& animation : m_animations) {
        ans.push_back(animation.name);
    }
    return ans;
}

void Model::set_current_animation(const std::string& name)
{
    m_current_animation_index = -1;
    for (int i = 0; i < m_animations.size(); ++i) {
        if (m_animations[i].name == name) {
            m_current_animation_index = i;
            break;
        }
    }
}

void Model::reset_animation_timer()
{
    m_timer = 0;
}

void Model::update(double delta_time)
{
    m_timer += delta_time;
    float curr_tick = 0;
    if (m_current_animation_index != -1) {
        auto& current_animation = m_animations[m_current_animation_index];
        curr_tick = fmod(m_timer * current_animation.ticks_per_second, current_animation.duration);
    }
    traverse_nodes(m_root_node.get(), Mat4::identity(), curr_tick);
}

void Model::set_joint_uniforms(charm::gl::Program& program)
{
    for (const auto& [bone_id, transform] : m_joint_transforms) {
        charm::gl::set_uniform(program, "u_joints[" + std::to_string(bone_id) + "]", transform);
    }
}

void Model::draw()
{
    for (int i = 0; i < m_vertex_arrays.size(); ++i) {
        gl::bind(m_vertex_arrays[i]);
        gl::draw_elements(GL_TRIANGLES, m_triangle_counts[i], GL_UNSIGNED_INT, nullptr);
    }
}

void Model::traverse_nodes(ch3db::Skeleton* node, const Mat4& parent_transform, float tick)
{
    Mat4 current_transform = parent_transform * node->transform;

    if (m_current_animation_index != -1) {
        for (const auto& [name, keyframes] : m_animations[m_current_animation_index].keyframes) {
            if (name != node->name)
                continue;

            for (int i = 0; i < keyframes.size(); ++i) {
                if (tick <= keyframes[i].time) {
                    float j = i - 1 >= 0 ? i - 1 : keyframes.size() - 1;
                    float t = (tick - keyframes[j].time) / (keyframes[i].time - keyframes[j].time);

                    auto v = Vec3(keyframes[i].position.x, keyframes[i].position.y, keyframes[i].position.z);
                    auto v_prev = Vec3(keyframes[j].position.x, keyframes[j].position.y, keyframes[j].position.z);
                    v = Vec3::lerp(v_prev, v, t);
                    auto translation = Mat4::translation(v.x(), v.y(), v.z());

                    auto q = Quat(keyframes[i].rotation.w, keyframes[i].rotation.x, keyframes[i].rotation.y, keyframes[i].rotation.z);
                    auto q_prev = Quat(keyframes[j].rotation.w, keyframes[j].rotation.x, keyframes[j].rotation.y, keyframes[j].rotation.z);
                    q = Quat::slerp(q_prev, q, t);
                    auto rotation = q.to_rotation();

                    // TODO: add scaling of bones

                    current_transform = parent_transform * translation * rotation;
                    break;
                }
            }
        }
    }

    m_joint_transforms[node->bone_id] = current_transform * node->inverse_bind_pose;
    for (const auto& child : node->children) {
        traverse_nodes(child.get(), current_transform, tick);
    }
}

}