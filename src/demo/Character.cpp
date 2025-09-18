#include "Character.h"

Character::Character()
{
    m_model = charm::ch3db::Model::read("res/demo/model.ch3db");
    for (const auto& mesh : m_model.meshes) {
        unsigned int vertex_array;
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);

        unsigned int vertex_buffer;
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(charm::ch3db::Vertex) * mesh.vertices.size(), &mesh.vertices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(charm::ch3db::Vertex), (void*)(offsetof(charm::ch3db::Vertex, position)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(charm::ch3db::Vertex), (void*)(offsetof(charm::ch3db::Vertex, normal)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(charm::ch3db::Vertex), (void*)(offsetof(charm::ch3db::Vertex, texcoord)));
        glEnableVertexAttribArray(3);
        glVertexAttribIPointer(3, 4, GL_INT, sizeof(charm::ch3db::Vertex), (void*)(offsetof(charm::ch3db::Vertex, bone_ids)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(charm::ch3db::Vertex), (void*)(offsetof(charm::ch3db::Vertex, bone_weights)));

        unsigned int index_buffer;
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indices.size(), &mesh.indices[0], GL_STATIC_DRAW);

        m_geometries.emplace_back(vertex_array, mesh.indices.size(), std::vector<unsigned int> { vertex_buffer, index_buffer });
    }
}

Character::~Character()
{
}

Character::Character(Character&& other)
{
}

Character& Character::operator=(Character&& other)
{
    if (this == &other)
        return *this;

    return *this;
}

std::vector<charm::Geometry>::const_iterator Character::begin() const
{
    return m_geometries.begin();
}

std::vector<charm::Geometry>::const_iterator Character::end() const
{
    return m_geometries.end();
}

void Character::update(double delta_time)
{
    auto& animation = m_model.animations[0];
    float tick = fmod(glfwGetTime() * animation.ticks_per_second, animation.duration);
    apply_animation(m_model.root.get(), charm::Mat4::identity(), tick);
}

void Character::setup_joint_uniform(charm::gl::Program& program)
{
    for (const auto& [bone_id, transform] : m_joint_transforms) {
        charm::gl::set_uniform(program, "u_joints[" + std::to_string(bone_id) + "]", transform);
    }
}

void Character::apply_animation(charm::ch3db::Skeleton* node, charm::Mat4 parent_transform, float tick)
{
    charm::Mat4 current_transform = parent_transform * node->transform;

    for (const auto& [name, keyframes] : m_model.animations[0].keyframes) {
        if (name != node->name)
            continue;

        for (int i = 0; i < keyframes.size(); ++i) {
            if (tick <= keyframes[i].time) {
                float j = i - 1 >= 0 ? i - 1 : keyframes.size() - 1;
                float t = (tick - keyframes[j].time) / (keyframes[i].time - keyframes[j].time);

                auto v = charm::Vec3(keyframes[i].position.x, keyframes[i].position.y, keyframes[i].position.z);
                auto v_prev = charm::Vec3(keyframes[j].position.x, keyframes[j].position.y, keyframes[j].position.z);
                v = charm::Vec3::lerp(v_prev, v, t);
                auto translation = charm::Mat4::translation(v.x(), v.y(), v.z());

                auto q = charm::Quat(keyframes[i].rotation.w, keyframes[i].rotation.x, keyframes[i].rotation.y, keyframes[i].rotation.z);
                auto q_prev = charm::Quat(keyframes[j].rotation.w, keyframes[j].rotation.x, keyframes[j].rotation.y, keyframes[j].rotation.z);
                q = charm::Quat::slerp(q_prev, q, t);
                auto rotation = q.to_rotation();

                current_transform = parent_transform * translation * rotation;
                break;
            }
        }
    }

    m_joint_transforms[node->bone_id] = current_transform * node->inverse_bind_pose;
    for (const auto& child : node->children) {
        apply_animation(child.get(), current_transform, tick);
    }
}
