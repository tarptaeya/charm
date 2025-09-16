#version 330 core

in vec2 v_texcoord;
in vec3 v_normal;
in vec3 v_color;

uniform sampler2D u_texture;

out vec4 FragColor;

vec3 LIGHT = vec3(1, 1, 1);

void main()
{
    vec3 normal = normalize(v_normal);
    vec4 color = texture(u_texture, v_texcoord);
    
    float d = max(dot(normal, LIGHT), 0.2);
    vec3 diffuse = d * vec3(color);

    FragColor = vec4(diffuse, 1);
    FragColor = vec4(v_color, 1);
}