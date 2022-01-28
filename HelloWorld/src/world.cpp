/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#include "world.h"

#include <iostream>

using namespace HelloWorld;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

World::World(int width, int height)
{
    if (!initGL(width, height))
        window_ = nullptr;

    wireframe_mode = false;
}

bool World::initGL(int width, int height)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window_ = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window_ == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

//    glEnable(GL_DEPTH_TEST);

    return true;
}

void World::render_loop()
{
    while (!glfwWindowShouldClose(window_))
    {
        // input
        // -----
        process_input_(window_, this);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (wireframe_mode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        for (auto &obj: world_objects_)
        {
            obj->shader->use();
            glBindVertexArray(obj->VAO_);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
    glfwTerminate();
}

void World::add_object(Object *obj)
{
    world_objects_.emplace_back(obj);
}

void World::set_process_input(void(*process_input)(GLFWwindow *, World *))
{
    process_input_ = process_input;
}

void World::switch_wireframe()
{
    wireframe_mode = !wireframe_mode;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}