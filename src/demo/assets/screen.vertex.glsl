#version 330 core

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec2 a_texcoord;

out vec2 v_texcoord;

void main()
{
    gl_Position = a_position;
    v_texcoord = a_texcoord;
}