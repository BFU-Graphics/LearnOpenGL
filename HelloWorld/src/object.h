/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#ifndef LEARNOPENGL_OBJECT_H
#define LEARNOPENGL_OBJECT_H

#include "shader.h"
#include "texture.h"
#include "world.h"
#include <vector>

namespace HelloWorld
{
    class Object
    {
    public:
        Object(float *vertices, int vertices_size, unsigned int *indices, int indices_size);

        Object(float *vertices, int vertices_size, float *text_coord, int text_coord_size, unsigned int *indices, int indices_size);

    public:
        Object(float *vertices, int vertices_size);
        void process_input(GLFWwindow *window, HelloWorld::World *world);
        void render();
    public:
        Shader                 *shader;
        std::vector<Texture *> textures;
    public:
        unsigned int VAO_;
        float deltaTime = 0.0f;	// time between current frame and last frame
        float lastFrame = 0.0f;
        glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    };
}


#endif //LEARNOPENGL_OBJECT_H
