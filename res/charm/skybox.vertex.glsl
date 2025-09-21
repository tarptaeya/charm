#version 330 core

layout (location = 0) in vec4 a_position;

uniform mat4 u_projection;
uniform mat4 u_view;

out vec3 v_texcoord;

void main()
{
    v_texcoord = vec3(a_position);
    vec4 position = u_projection * mat4(mat3(u_view)) * a_position;
    gl_Position = position.xyww;
}