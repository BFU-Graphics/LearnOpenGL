/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#include "world.h"
#include "camera.h"
#include "object.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
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

    HelloWorld::Shader  shader("commonwithtexture.vert", "commonwithtexture.frag");
    HelloWorld::Shader  lightingShader("colors.vert", "colors.frag");
    HelloWorld::Shader lightCubeShader("light.vert", "light.frag");
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
    };

//    unsigned int indices[] = {
//            0, 1, 3, // first triangle
//            1, 2, 3  // second triangle
//    };

    HelloWorld::Object obj(vertices, sizeof(vertices));

    obj.shader = &lightingShader;
    obj.shader_ = &lightCubeShader;

    world.add_object(&obj);
//    HelloWorld::Texture texture1("container.jpg");
//    HelloWorld::Texture texture2("awesomeface.png");
//
//    HelloWorld::Shader use();
//    shader.set_int("texture1", 0);
//    shader.set_int("texture2", 1);
    world.render_loop();

    return 0;
}
