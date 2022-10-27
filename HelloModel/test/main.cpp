#include "world.h"
#include "shader.h"
#include "model.h"

#include <iostream>

void process_input(GLFWwindow *window, HelloModel::World *world)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        world->switch_wireframe();
    }
}

int main()
{
    HelloModel::World world;
    HelloModel::Shader shader("common_model.vert", "common_model.frag");
    HelloModel::Model model("sphere.obj");

    world.set_process_input(process_input);

    model.shader_ = &shader;
    world.add_model(&model);
    world.render_loop();
    return 0;
}
