#version 330 core

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;
layout (location = 3) in ivec4 a_bone_ids;
layout (location = 4) in vec4 a_bone_weights;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_texcoord;
out vec3 v_normal;
out vec3 v_color;

void main()
{
    gl_Position = u_projection * u_view * u_model * a_position;
    v_texcoord = a_texcoord;
    v_normal = inverse(transpose(mat3(u_model))) * a_normal;

    v_color = vec3(0, 0, 0);
    for (int i = 0; i < 4; ++i) {
        if (a_bone_ids[i] == 6) {
            v_color = vec3(a_bone_weights[i], 0, 0);
        }
    }
}