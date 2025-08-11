#version 330 core

in vec2 v_texcoord;
in vec3 v_normal;

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(v_normal);

    FragColor = vec4(normal, 1);
}