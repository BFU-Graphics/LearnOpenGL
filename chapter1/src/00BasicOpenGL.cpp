/**
 * 头文件：GLAD 与 GLFW
 * GLAD是一个更方便使用OpenGL的库，它会加载所有的OpenGL函数指针，所以我们不需要在每个OpenGL函数前面加上gl前缀
 * GLFW是一个用于管理OpenGL上下文的库，它可以让我们创建一个窗口，处理用户输入，以及管理OpenGL上下文
 *
 * 注意点：从上面两行我们知道，GLFW只是个用来使用OpenGL创建窗口用的，所以在include的时候，一定要先include GLAD，再include GLFW。否则就会报错！
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/**
 * 想要使用GLFW，必须要先初始化。初始化的方法很固定，就那么几行就可以。
 */
void init_glfw()
{
    glfwInit(); // 初始化GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 指定OpenGL主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 指定OpenGL次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 指定OpenGL的模式

    // 在MacOS系统中，必须要加上下面这行代码，否则会报错
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

/**
 * 初始化GLAD
 */
auto init_glad() -> bool
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

/**
 * 创建一个窗口对象
 */
auto create_window(int width, int height) -> GLFWwindow *
{
    GLFWwindow *window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window); // 将窗口的上下文设置为当前线程的主上下文

    return window;
}

auto main() -> int
{
    // 先执行初始化步骤。这个顺序非常重要，一定要先初始化GLFW，再初始化GLAD。

    // 第一步：初始化GLFW
    init_glfw();

    // 第二步：创建一个窗口对象
    auto *window = create_window(800, 600);

    // 第三步：初始化GLAD
    init_glad();

    // 进入渲染循环
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 设置清屏颜色（只是一个设置而已，还没有生效。可以在任何地方设置都没关系，不是一定要在渲染循环内设置。）
        glClear(GL_COLOR_BUFFER_BIT); // 执行清屏操作

        glfwSwapBuffers(window); // 交换帧缓冲
        glfwPollEvents(); // 读取事件操作（比如键盘输入等）
    }

    return 0;
}
