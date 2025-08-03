#version 330 core

in vec3 v_color;
in vec2 v_texcoord;

uniform sampler2D u_texture;

out vec4 FragColor;

void main()
{
    vec4 t_color = texture(u_texture, v_texcoord);
    vec4 color = mix(t_color, vec4(v_color, 1.0f), 0.2);
    FragColor = color;
}