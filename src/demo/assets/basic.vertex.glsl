#version 330 core

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec3 a_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_texcoord;
out vec3 v_normal;

void main()
{
    gl_Position = u_projection * u_view * u_model * a_position;
    v_texcoord = a_texcoord;
    v_normal = inverse(transpose(mat3(u_model))) * a_normal;
}