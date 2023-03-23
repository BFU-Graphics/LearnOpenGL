#version 330 core
out vec4 FragColor;

uniform vec3 LightColor;

void main()
{
    vec3 ambient = 0.1 * LightColor;
    vec3 diffuse = LightColor;
    vec3 specular = LightColor;
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result,1.0);
}
