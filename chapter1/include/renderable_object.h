#ifndef LEARNOPENGL_RENDERABLE_OBJECT_H
#define LEARNOPENGL_RENDERABLE_OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <array>
#include <vector>

#include "shader.h"
#include "texture.h"

class RenderableObject
{
public:
    unsigned int ID;

public:
    RenderableObject(float vertices_array[], int vertices_array_size, unsigned int indices_array[], int indices_array_size, const std::string &texture_path);
    RenderableObject(const std::string& model_path);

public:
    void render(const Shader &shader); // 使用这个shader来渲染这个物体

public:
    struct Vertex
    {
        std::array<float, 3> position;
        std::array<float, 3> color;
        std::array<float, 3> tex_coords;
    };

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Texture texture;
};

#endif //LEARNOPENGL_RENDERABLE_OBJECT_H
