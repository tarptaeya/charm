#version 330 core

layout (location = 0) in vec4 a_position;

uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * a_position;
}