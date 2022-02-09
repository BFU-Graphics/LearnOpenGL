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

        Object(float *vertices, int vertices_size);

    public:
        void render();

    public:
        Shader                 *shader;
        Shader                 *shader_;
        std::vector<Texture *> textures;
    public:
        unsigned int VAO_;
        unsigned int VAO_light;//以后要修改只用一个VAO 因为步骤是一样的
        glm::vec3 position_;

        void render1();
    };
}




#endif //LEARNOPENGL_OBJECT_H
