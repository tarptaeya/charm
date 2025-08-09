#version 330 core

in vec2 v_texcoord;
in vec3 v_normal;

uniform sampler2D u_texture_1;
uniform sampler2D u_texture_2;

out vec4 FragColor;

void main()
{
    vec4 t1_color = texture(u_texture_1, v_texcoord);
    vec4 t2_color = texture(u_texture_2, v_texcoord);
    vec4 color = mix(t1_color, t2_color, 0.5);
    FragColor = vec4(1, 0, 0, 1);
}