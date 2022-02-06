/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#include "world.h"

#include "texture.h"

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

    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };

    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

//    float texCoords[] = {
//            0.0f, 0.0f, // 左下角
//            1.0f, 0.0f, // 右下角
//            0.5f, 1.0f // 上中
//    };

    HelloWorld::Object obj(vertices, sizeof(vertices),indices,sizeof(indices));

    obj.shader = &shader;

    world.add_object(&obj);
//    (HelloWorld::Texture("container.jpg"));
//    HelloWorld::Texture Texture("awesomeface.png");
    HelloWorld::Texture texture1("mitsuba2.png");
    HelloWorld::Texture texture2("awesomeface.png");

    HelloWorld::Shader use();
    glUniform1i(glGetUniformLocation(shader.ID_, "texture1"), 0);
    shader.set_int("texture2", 1);
    world.render_loop();

    return 0;
}
