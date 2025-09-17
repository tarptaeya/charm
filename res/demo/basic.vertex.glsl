#version 330 core

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;
layout (location = 3) in ivec4 a_bone_ids;
layout (location = 4) in vec4 a_bone_weights;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_joints[32];

out vec2 v_texcoord;
out vec3 v_normal;

void main()
{
    mat4 bone = mat4(0.0f);
    for (int i = 0; i < 4; ++i) {
        bone += a_bone_weights[i] * u_joints[a_bone_ids[i]];
    }

    mat4 world = u_model * bone;
    gl_Position = u_projection * u_view * world * a_position;
    v_texcoord = a_texcoord;
    v_normal = inverse(transpose(mat3(world))) * a_normal;
}