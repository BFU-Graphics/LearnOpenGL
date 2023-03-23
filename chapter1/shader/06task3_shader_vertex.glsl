#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

///原本的样子是被注释的语句

// out vec3 ourColor;
out vec3 ourPosition;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    // ourColor = aColor;
    ourPosition = aPos;
}
