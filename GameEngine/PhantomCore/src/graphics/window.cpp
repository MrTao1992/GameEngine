#include "window.h"
extern double mouse_x;
extern double mouse_y;

namespace phantom
{
    namespace graphics
    {
        Window::Window(const char *title, int width, int height)
        {
            m_Title = title;
            m_Width = width;
            m_Height = height;
            if (!init())
                glfwTerminate();
        }

        Window::~Window()
        {
            glfwTerminate();
        }

        bool Window::init()
        {
            if (!glfwInit())
            {
                std::cout << "Failed to initialize GLFW!" << std::endl;
                return false;
            }
            //版本号 opengl3.0 (举例)
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            // Make the window resize-able.
            glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
            m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
            if (!m_Window)
            {
                std::cout << "Failed to create GLFW window!" << std::endl;
                return false;
            }
            glfwSetKeyCallback(m_Window, key_callback);
            glfwSetWindowSizeCallback(m_Window, windowResize);
            glfwSetCursorPosCallback(m_Window, cursor_position_callback);
            glfwMakeContextCurrent(m_Window);
            //设置glfw的刷帧率
            glfwSwapInterval(1);

            // must after  glfwMakeContextCurrent
            if (glewInit() != GLEW_OK)
            {
                std::cout << "Failed to initialize glew!" << std::endl;
                glfwTerminate();
                return false;
            }

            std::cout << glGetString(GL_VERSION) << std::endl;
            return true;
        }

        void Window::clear() const
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void Window::update()
        {
            glfwPollEvents();
            glfwSwapBuffers(m_Window);
            GLenum error = glGetError();
            if (error != GL_NO_ERROR)
            {
                std::cout << "GL is error" << error << std::endl;
            }
        }

        bool Window::closed() const
        {
            return glfwWindowShouldClose(m_Window) == 1;
        }

        /**
        * 销毁终止GL
        * */
        void Window::terminate() const
        {

            glfwDestroyWindow(m_Window);
            glfwTerminate();
        }

        void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
        {
            mouse_x = xpos;
            mouse_y = ypos;
        }

        void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        void windowResize(GLFWwindow *window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
    }
}