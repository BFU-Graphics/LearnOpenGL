#ifndef LEARNOPENGL_WORLD_H
#define LEARNOPENGL_WORLD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "model.h"

namespace HelloModel
{
    class World
    {
    public:
        explicit World(int width = 1280, int height = 800);

        void render_loop();

        void add_model(Model *model);

    public:
        void set_process_input(void(*process_input)(GLFWwindow *, World *));

        void switch_wireframe();

    private:
        bool initGL(int width, int height);

    private:
        GLFWwindow *window_;
        bool wireframe_mode_;
        void (*process_input_)(GLFWwindow *, World *);

    private:
        std::vector<Model *> world_objects_;
    };
}

#endif //LEARNOPENGL_WORLD_H
