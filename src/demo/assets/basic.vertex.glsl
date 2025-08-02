#version 330 core

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec3 a_color;

uniform mat4 u_model;
uniform mat4 u_projection;

out vec3 v_color;

void main()
{
    gl_Position = u_projection * u_model * a_position;
    v_color = a_color;
}