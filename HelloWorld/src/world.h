/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#ifndef LEARNOPENGL_WORLD_H
#define LEARNOPENGL_WORLD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "object.h"
#include "shader.h"

#include <vector>
#include <map>
#include <functional>

namespace HelloWorld
{
    class World
    {
    public:
        World(int width, int height);

        void render_loop();

        void add_object(Object *obj, Shader *shader);

    public:
        void set_process_input(void(*process_input)(GLFWwindow *, World *));

        void switch_wireframe();

    private:
        bool initGL(int width, int height);

    private:
        GLFWwindow                   *window_;
        std::map<Object *, Shader *> world_objects_;
        bool                         wireframe_mode;

        void (*process_input_)(GLFWwindow *, World *);
    };
}


#endif //LEARNOPENGL_WORLD_H
