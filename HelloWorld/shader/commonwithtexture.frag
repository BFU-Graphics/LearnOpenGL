#version 330 core
out vec4 FragColor;


void main()
{
    // linearly interpolate between both textures (80% container, 20% awesomeface)
    FragColor = vec4(0.5, 0.3, 0.8, 1.0f);
}