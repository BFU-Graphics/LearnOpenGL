#include "world.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

HelloModel::World::World(int width, int height)
{
    if (!initGL(width, height))
        window_ = nullptr;

    wireframe_mode_ = false;
}

void HelloModel::World::render_loop()
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

        if (wireframe_mode_)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        for (auto &obj: world_objects_)
            obj->draw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
    glfwTerminate();
}

void HelloModel::World::add_model(HelloModel::Model *model)
{
    world_objects_.emplace_back(model);
}

void HelloModel::World::switch_wireframe()
{
    wireframe_mode_ = !wireframe_mode_;
}

bool HelloModel::World::initGL(int width, int height)
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
    return true;
}

void HelloModel::World::set_process_input(void (*process_input)(GLFWwindow *, World *))
{
    process_input_ = process_input;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}