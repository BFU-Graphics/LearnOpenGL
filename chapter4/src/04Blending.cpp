#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void init_glfw();
auto init_glad() -> bool;
auto create_window(int width, int height) -> GLFWwindow *;
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#include "../include/shader.h"
#include "../include/texture.h"
#include "../include/renderable_object.h"
#include "../include/camera.h"
#include "../include/object.h"

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 800.f / 2.0f;
float lastY = 600.f / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

auto main() -> int
{
    init_glfw();
    auto *window = create_window(800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    init_glad();

    Shader shader(MY_SHADER_DIR + std::string("01shader_vertex.glsl"), MY_SHADER_DIR + std::string("04shader_fragment.glsl"));

    ///这里没有用到的是color,懒得删了
    std::array<float, 288> cube_vertices = {
            // positions         // colors         // texture coords
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f

    };

    std::array<unsigned int, 36> cube_indices = {0, 1, 2,
                                                 3, 4, 5,
                                                 6, 7, 8,
                                                 9, 10, 11,
                                                 12, 13, 14,
                                                 15, 16, 17,
                                                 18, 19, 20,
                                                 21, 22, 23,
                                                 24, 25, 26,
                                                 27, 28, 29,
                                                 30, 31, 32,
                                                 33, 34, 35,
    };

    std::array<float, 48> plane_vertices = {
            // positions         // colors         // texture coords
            5.0f, -0.5f,  5.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.0f,
            -5.0f, -0.5f,  5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f,

            5.0f, -0.5f,  5.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f,
            5.0f, -0.5f, -5.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f
    };

    std::array<unsigned int, 6> plane_indices = {0, 1, 2,
                                                  3, 4, 5,
    };

    std::array<float, 48> transparent_vertices = {
            0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
            0.0f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  1.0f,
            1.0f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f,

            0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,
            1.0f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  1.0f,
            1.0f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f
    };

    /// 既然和plane的顺序一样那就不写这个了省一点空间
/*    std::array<unsigned int, 6> transparent_indices = {0, 1, 2,
                                                  3, 4, 5,
    };*/

    std::vector<glm::vec3> vegetation
    {
            glm::vec3(-1.5f, 0.0f, -0.48f),
            glm::vec3( 1.5f, 0.0f, 0.51f),
            glm::vec3( 0.0f, 0.0f, 0.7f),
            glm::vec3(-0.3f, 0.0f, -2.3f),
            glm::vec3 (0.5f, 0.0f, -0.6f)
    };

    Object cube(cube_vertices.data(), sizeof(cube_vertices), cube_indices.data(), sizeof(cube_indices));
    Texture texture1(MY_TEXTURE_DIR + std::string("marble.jpg"));
    Object plane(plane_vertices.data(), sizeof(plane_vertices), plane_indices.data(), sizeof(plane_indices));
    Texture texture2(MY_TEXTURE_DIR + std::string("metal.png"));
    Object grass(transparent_vertices.data(), sizeof(transparent_vertices), plane_indices.data(), sizeof(plane_indices));
    Texture texture3(MY_TEXTURE_DIR + std::string("grass.png"));

    shader.use();
    shader.set_int("texture1", 0);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        /// 深度测试
        glDepthFunc(GL_LESS); // 在片段深度值小于缓冲的深度值时通过测试

        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        shader.use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.f / 600.f, 0.1f, 100.0f);
        shader.set_mat4("projection", projection);
        shader.set_mat4("view", view);

        glActiveTexture(GL_TEXTURE0);
        texture1.bind();
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        shader.set_mat4("model", model);
        cube.renderCube(shader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        shader.set_mat4("model", model);
        cube.renderCube(shader);

        glActiveTexture(GL_TEXTURE0);
        /// 其实这句话也不用写这么多遍的，但是写了就懒得删了
        texture2.bind();
        shader.set_mat4("model", glm::mat4(1.0f));
        plane.render(shader);

        glActiveTexture(GL_TEXTURE0);
        texture3.bind();
        for (unsigned int i = 0; i < vegetation.size(); i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, vegetation[i]);
            shader.set_mat4("model", model);
            grass.render(shader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void init_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

auto init_glad() -> bool
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

auto create_window(int width, int height) -> GLFWwindow *
{
    GLFWwindow *window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    return window;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

