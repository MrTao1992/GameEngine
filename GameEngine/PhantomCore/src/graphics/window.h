#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace phantom
{
    namespace graphics
    {

        class Window
        {
        private:
            const char *m_Title;
            int m_Width, m_Height;
            GLFWwindow *m_Window;
            bool m_Closed;

        public:
            Window(const char *name, int width, int height);
            ~Window();
            void clear() const;
            void update();
            bool closed() const;
            void terminate() const;
            inline int getWidth() const { return m_Width; }
            inline int getHeight() const { return m_Height; }
            friend void windowResize(GLFWwindow *window, int width, int height);
            //添加键盘事件回调
            friend void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
            //添加鼠标事件
            friend void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

        private:
            bool init();
        };

    }
}