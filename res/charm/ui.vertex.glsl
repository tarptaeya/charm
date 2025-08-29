#version 330 core

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec3 a_color;
layout (location = 2) in int a_active_texture;
layout (location = 3) in vec2 a_texcoord;

uniform mat4 u_projection;

out vec3 v_color;
flat out int v_active_texture;
out vec2 v_texcoord;

void main()
{
    gl_Position = u_projection * a_position;
    v_color = a_color;
    v_active_texture = a_active_texture;
    v_texcoord = a_texcoord;
}