#include "Duck.h"

Duck::Duck()
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

Duck::~Duck()
{
}

Duck::Duck(Duck&& other)
{
}

Duck& Duck::operator=(Duck&& other)
{
    if (this == &other)
        return *this;

    return *this;
}

std::vector<charm::Geometry>::const_iterator Duck::begin() const
{
    return m_geometries.begin();
}

std::vector<charm::Geometry>::const_iterator Duck::end() const
{
    return m_geometries.end();
}

void Duck::update(double delta_time)
{
    auto& animation = m_model.animations[0];
    float tick = fmod(0.5 * glfwGetTime() * animation.ticks_per_second, animation.duration);
    apply_animation(m_model.root.get(), charm::Mat4::identity(), tick);
}

void Duck::setup_joint_uniform(charm::gl::Program& program)
{
    for (const auto& [bone_id, transform] : m_joint_transforms) {
        charm::gl::Context::set_uniform(program, "u_joints[" + std::to_string(bone_id) + "]", transform);
    }
}

void Duck::apply_animation(charm::ch3db::Skeleton* node, charm::Mat4 parent_transform, float tick)
{
    charm::Mat4 current_transform = parent_transform * node->transform;

    for (const auto& [name, keyframes] : m_model.animations[0].keyframes) {
        if (name != node->name)
            continue;

        for (int i = 0; i < keyframes.size(); ++i) {
            if (tick <= keyframes[i].time) {
                auto translation = charm::Mat4::translation(keyframes[i].position.x, keyframes[i].position.y, keyframes[i].position.z);
                auto q = keyframes[i].rotation;
                auto rotation = charm::Mat4({
                    // clang-format off
                    { 1 - 2 * (q.y * q.y + q.z * q.z),     2 * (q.x * q.y - q.w * q.z),     2 * (q.x * q.z + q.w * q.y),     0 },
                    { 2 * (q.x * q.y + q.w * q.z),         1 - 2 * (q.x * q.x + q.z * q.z), 2 * (q.y * q.z - q.w * q.x),     0 },
                    { 2 * (q.x * q.z - q.w * q.y),         2 * (q.y * q.z + q.w * q.x),     1 - 2 * (q.x * q.x + q.y * q.y), 0 },
                    { 0,                                   0,                               0,                               1 }
                    // clang-format on
                });
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
