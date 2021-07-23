#include "DefaultApplication.h"

namespace Phantom
{
    DefaultApplication::DefaultApplication(GfxConfiguration &config)
        : BaseApplication(config){};
    int DefaultApplication::Initialize()
    {
        if (!glfwInit())
        {
            std::cout << "Failed to initialize GLFW!" << std::endl;
            return -1;
        }
        //版本号 opengl3.0 (举例)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        // Make the window resize-able.
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        int m_Width = 800;
        int m_Height = 600;
        m_Window = glfwCreateWindow(m_Width, m_Height, "DefaultAppLication", NULL, NULL);
        if (!m_Window)
        {
            std::cout << "Failed to create GLFW window!" << std::endl;
            return -1;
        }
        glfwSetKeyCallback(m_Window, key_callback);
        glfwSetWindowSizeCallback(m_Window, windowResize);
        glfwSetCursorPosCallback(m_Window, cursor_position_callback);
        glfwMakeContextCurrent(m_Window);
        //设置glfw的刷帧率
        glfwSwapInterval(1);

        // must after  glfwMakeContextCurrent
        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize glew!" << std::endl;
            glfwTerminate();
            return -1;
        }

        std::cout << glGetString(GL_VERSION) << std::endl;
        return 0;
    }
    void DefaultApplication::Finalize()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
    void DefaultApplication::Tick()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cout << "GL is error" << error << std::endl;
        }
    }

    void DefaultApplication::windowResize(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
    //添加键盘事件回调
    void DefaultApplication::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    //添加鼠标事件
    void DefaultApplication::cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
    {
    }
}