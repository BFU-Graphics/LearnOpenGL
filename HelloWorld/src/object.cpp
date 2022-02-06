/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

using namespace HelloWorld;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Object::Object(float *vertices, int vertices_size, unsigned int *indices, int indices_size)
{
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

Object::Object(float *vertices, int vertices_size)
{
    unsigned int VBO;
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

//    glGenVertexArrays(1, &VAO_light);
//    glBindVertexArray(VAO_light);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void Object::render()
{
    if (!textures.empty())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures.front()->ID_);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures.back()->ID_1);
    }

//    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));
//    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//    //transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));
//    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));

    shader->use();//激活着色器

//    shader->set_vec3("objectColor", 1.0f, 0.5f, 0.31f);
//    shader->set_vec3("lightColor",  1.0f, 1.0f, 1.0f);
//    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//    glm::mat4 view = camera.GetViewMatrix();
//    shader->set_mat4("projection", projection);
//    shader->set_mat4("view", view);
//
//    glm::mat4 model = glm::mat4(1.0f);
//    shader->set_mat4("model", model);
    //第一次 lightingShader.use();
    // 初始化
//    glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 view          = glm::mat4(1.0f);
//    glm::mat4 projection    = glm::mat4(1.0f);
//    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
//    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//    第一个参数定义了fov的值，它表示的是视野(Field of View)，并且设置了观察空间的大小。如果想要一个真实的观察效果，它的值通常设置为45.0f，但想要一个末日风格的结果你可以将其设置一个更大的值。
//    第二个参数设置了宽高比，由视口的宽除以高所得。
//     第三和第四个参数设置了平截头体的近和远平面。我们通常设置近距离为0.1f，而远距离设为100.0f。
//     所有在近平面和远平面内且处于平截头体内的顶点都会被渲染。
//     retrieve the matrix uniform locations
//    将矩阵传入着色器
//    unsigned int modelLoc = glGetUniformLocation(shader->ID_, "model");
//    unsigned int viewLoc  = glGetUniformLocation(shader->ID_, "view");
//    // pass them to the shaders (3 different ways)
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
//    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//    shader->set_mat4("projection", projection);

//    unsigned int transformLoc = glGetUniformLocation(shader->ID_, "transform");
//    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    //我们首先查询uniform变量的地址，然后用有Matrix4fv后缀的glUniform函数把矩阵数据发送给着色器。
    // 第一个参数是uniform的位置值。
    // 第二个参数告诉OpenGL我们将要发送多少个矩阵，这里是1。
    // 第三个参数询问我们我们是否希望对我们的矩阵进行置换(Transpose)，也就是说交换我们矩阵的行和列。
    //最后一个参数是真正的矩阵数据，但是GLM并不是把它们的矩阵储存为OpenGL所希望接受的那种，因此我们要先用GLM的自带的函数value_ptr来变换这些数据。
//    //偏移量
//    float offset = 0.5f;
//    shader->set_float("xOffset", offset);

    glBindVertexArray(VAO_);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glDrawArrays(GL_TRIANGLES, 0, 3);

//    transform = glm::mat4(1.0f); // reset it to identity matrix
//    transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
//    float scaleAmount = static_cast<float>(sin(glfwGetTime()));
//    transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
//    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
    // this time take the matrix value array's first element as its memory pointer value

//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//    shader_->use();
//    shader_->set_mat4("projection", projection);
//    shader_->set_mat4("view", view);
//    model = glm::mat4(1.0f);
//    model = glm::translate(model, lightPos);
//    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
//    shader_->set_mat4("model", model);
//
//    glBindVertexArray(VAO_light);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Object::Object(float *vertices, int vertices_size, float *text_coord, int text_coord_size, unsigned int *indices, int indices_size)
{
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
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

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}