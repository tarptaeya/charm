#version 330 core

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 v_texcoord;
in vec3 v_normal;

uniform sampler2D u_texture;
uniform DirectionalLight u_directional_light;

out vec4 FragColor;

vec3 calculate_directional_light(DirectionalLight light, vec3 normal)
{
    vec4 color = texture(u_texture, v_texcoord);
    vec3 normalized_light_direction = normalize(-light.direction);
    float kd = max(dot(normal, normalized_light_direction), 0.0);
    vec3 ambient = light.ambient * vec3(color);
    vec3 diffuse = kd * light.diffuse * vec3(color);
    return ambient + diffuse;
}

void main()
{
    FragColor = vec4(calculate_directional_light(u_directional_light, v_normal), 1);
}