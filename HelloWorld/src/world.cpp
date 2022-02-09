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

Camera camera;
float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(0.6f, 0.0f, 2.0f);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

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
    glfwSetCursorPosCallback(window_, mouse_callback);
    glfwSetScrollCallback(window_, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    return true;
}

void World::render_loop() {

    while (!glfwWindowShouldClose(window_)) {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        process_input_(window_, this, &camera, deltaTime);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (wireframe_mode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        for (auto &obj: world_objects_) {
            obj->shader->use();
            obj->shader->set_int("material.diffuse", 0);
            obj->shader->set_vec3("light.position", lightPos);
            obj->shader->set_vec3("viewPos", camera.Position);

            obj->shader->set_vec3("light.ambient",  0.2f, 0.2f, 0.2f);
            obj->shader->set_vec3("light.diffuse",  0.5f, 0.5f, 0.5f); // 将光照调暗了一些以搭配场景
            obj->shader->set_vec3("light.specular", 1.0f, 1.0f, 1.0f);

            // material properties
            obj->shader->set_vec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
            obj->shader->set_float("material.shininess", 64.0f);

            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) 800 / (float) 600, 0.1f, 100.0f);
            obj->shader->set_mat4("projection", projection);
            glm::mat4 view = camera.GetViewMatrix();
            obj->shader->set_mat4("view", view);
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            obj->shader->set_mat4("model", model);
            obj->render();

            obj->shader_->use();
            //projection = glm::perspective(glm::radians(camera.Zoom), (float) 800 / (float) 600, 0.1f, 100.0f);
            obj->shader_->set_mat4("projection", projection);
            //view = camera.GetViewMatrix();
            obj->shader_->set_mat4("view", view);
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f));
            obj->shader_->set_mat4("model", model);
            obj->render1();
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

void World::set_process_input(void(*process_input)(GLFWwindow *, World *, Camera *camera, float deltaTime)) {
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

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}