#version 330 core

in vec2 v_texcoord;

uniform sampler2D u_font_texture;

out vec4 FragColor;

void main()
{
    vec4 color = texture(u_font_texture, v_texcoord);
    FragColor = color;
}