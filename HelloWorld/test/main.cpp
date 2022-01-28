/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#include "world.h"

void process_input(GLFWwindow *window, HelloWorld::World *world)
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
    HelloWorld::World world(1000, 800);

    world.set_process_input(process_input);

    HelloWorld::Shader shader("common.vert", "common.frag");

    float vertices[] = {
            0.5f, 0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f, 0.5f, 0.0f   // top left
    };

    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    HelloWorld::Object obj(vertices, sizeof(vertices), indices, sizeof(indices));
    obj.shader = &shader;
    obj.textures.emplace_back();

    world.add_object(&obj);

    world.render_loop();

    return 0;
}
