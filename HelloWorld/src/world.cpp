/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "world.h"

#include "texture.h"

#include <iostream>

using namespace HelloWorld;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

World::World(int width, int height) {
    if (!initGL(width, height))
        window_ = nullptr;

    wireframe_mode = false;
}

bool World::initGL(int width, int height) {
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
    if (window_ == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

//    glEnable(GL_DEPTH_TEST);

    return true;
}

void World::render_loop() {

    while (!glfwWindowShouldClose(window_)) {
        // per-frame time logic
        // --------------------
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
        // input
        // -----
        process_input_(window_, this);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (wireframe_mode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        for (auto &obj: world_objects_) {
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) 800 / (float) 600, 0.1f, 100.0f);
            obj->shader->set_mat4("projection", projection);
            glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            float radius = 10.0f;
            float camX = static_cast<float>(sin(glfwGetTime()) * radius);
            float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
            view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            obj->shader->set_mat4("view", view);
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, obj->position_);
            float angle = 20.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            obj->shader->set_mat4("model", model);
            obj->render();
        }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
    glfwTerminate();
}

void World::add_object(Object *obj) {
    world_objects_.emplace_back(obj);
}

void World::set_process_input(void(*process_input)(GLFWwindow *, World *)) {
    process_input_ = process_input;
}

void World::switch_wireframe() {
    wireframe_mode = !wireframe_mode;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}