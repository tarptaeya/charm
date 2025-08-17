#version 330 core

in vec3 v_color;
flat in int v_active_texture;
in vec2 v_texcoord;

uniform sampler2D u_font_texture;

out vec4 FragColor;

void main()
{
    if (v_active_texture == 0) {
        FragColor = vec4(v_color, 1);
    } else if (v_active_texture == 1) {
        vec4 color = texture(u_font_texture, v_texcoord);
        FragColor = vec4(color.r * v_color, color.r * color.r);
    }
    
}