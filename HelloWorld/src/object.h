/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#ifndef LEARNOPENGL_OBJECT_H
#define LEARNOPENGL_OBJECT_H

#include "shader.h"
#include "texture.h"

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

        void render();

    public:
        Shader                 *shader;
        std::vector<Texture *> textures;
    public:
        unsigned int VAO_;
    };
}


#endif //LEARNOPENGL_OBJECT_H
