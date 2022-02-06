#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec3 ourPosition;
void main()
{
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = vec4(ourColor, 1.0f);
    //FragColor = vec4(ourPosition, 1.0);
}
