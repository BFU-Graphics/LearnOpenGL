#ifndef LEARNOPENGL_TEXTURE_H
#define LEARNOPENGL_TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

class Texture
{
public:
    unsigned int ID;

public:
    Texture(const std::string &texture_path);
    void bind();
};
#endif //LEARNOPENGL_TEXTURE_H
