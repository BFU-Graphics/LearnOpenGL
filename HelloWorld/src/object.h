/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#ifndef LEARNOPENGL_OBJECT_H
#define LEARNOPENGL_OBJECT_H

namespace HelloWorld
{
    class Object
    {
    public:
        Object(float* vertices, int vertices_size, unsigned int* indices, int indices_size);
    public:
        unsigned int VAO_;
    };
}


#endif //LEARNOPENGL_OBJECT_H
