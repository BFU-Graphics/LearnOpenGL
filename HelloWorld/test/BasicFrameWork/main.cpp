/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#include "world.h"
#include "object.h"
#include "texture.h"
//#include "camera.h"
//void process_input(GLFWwindow *window, HelloWorld::World *world)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//    {
//        world->switch_wireframe();
//    }
//    float cameraSpeed = static_cast<float>(2.5 * HelloWorld::Object deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        HelloWorld::Object cameraPos += cameraSpeed * HelloWorld::Object cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        HelloWorld::Object cameraPos -= cameraSpeed * HelloWorld::Object cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        HelloWorld::Object cameraPos -= glm::normalize(glm::cross(HelloWorld::Object cameraFront, HelloWorld::Object cameraUp)) * cameraSpeed;
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        HelloWorld::Object cameraPos += glm::normalize(glm::cross(HelloWorld::Object cameraFront, HelloWorld::Object cameraUp)) * cameraSpeed;
//}

int main()
{
    HelloWorld::World world(1000, 800);
    //world.set_process_input(process_input);
    HelloWorld::Object process_input(GLFWwindow *window, HelloWorld::World *world);
    //world.set_process_input(process_input);
    HelloWorld::Shader  shader("commonwithtexture.vert", "commonwithtexture.frag");

    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


//    unsigned int indices[] = {
//            0, 1, 3, // first triangle
//            1, 2, 3  // second triangle
//    };

    HelloWorld::Object obj(vertices, sizeof(vertices));

    obj.shader = &shader;

    world.add_object(&obj);
//    (HelloWorld::Texture("container.jpg"));
//    HelloWorld::Texture Texture("awesomeface.png");
    HelloWorld::Texture texture1("container.jpg");
    HelloWorld::Texture texture2("awesomeface.png");

    HelloWorld::Shader use();
    shader.set_int("texture1", 0);
    shader.set_int("texture2", 1);
    world.render_loop();

    return 0;
}
